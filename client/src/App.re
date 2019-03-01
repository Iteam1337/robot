let s = ReasonReact.string;

type state = {
  displayMode: Mode.t,
  displayTime: float,
  ws: array(WebSocket.t),
};

type action =
  | ToggleTime(float)
  | ChangeDislayMode(Mode.t)
  | UpdateTranslation(WebSocket.t);

let component = ReasonReact.reducerComponent(__MODULE__);

module Style = {
  open Emotion;

  let translations = [%css
    [
      padding(`px(20)),
      paddingTop(`px(150)),
      display(`inlineFlex),
      flexDirection(`column),
      overflow(`scroll),
      width(`pct(100.0)),
    ]
  ];
};

let make = _children => {
  ...component,

  initialState: () => {displayMode: Conversation, displayTime: 0.0, ws: [||]},

  didMount: self => {
    WebSocket.(
      socket->listen("message", data =>
        self.send(UpdateTranslation(data->Decode.message->Decode.response))
      )
    )
    |> ignore;
  },

  reducer: (action, state) => {
    switch (action) {
    | ChangeDislayMode(mode) =>
      ReasonReact.Update({...state, displayMode: mode})
    | ToggleTime(displayTime) =>
      ReasonReact.Update({
        ...state,
        displayTime: displayTime === state.displayTime ? 0.0 : displayTime,
      })
    | UpdateTranslation(ws) =>
      ReasonReact.Update({
        ...state,
        ws: [|ws|]->Belt.Array.concat(state.ws),
      })
    };
  },

  render: ({send, state}) => {
    <>
      <Header
        currentDisplayMode={state.displayMode}
        changeDisplayMode={mode => send(ChangeDislayMode(mode))}
      />
      {switch (state.displayMode, state.ws->Belt.Array.length) {
       | (_, 0) => <EmptyState />
       | (Presentation, _) => <Presentation translations={state.ws} />
       | (Conversation, _) =>
         <ul className=Style.translations id="list">
           {state.ws
            ->Belt.Array.mapWithIndex((i, translation) => {
                let previousOrigin =
                  switch (state.ws->Belt.Array.get(i - 1)) {
                  | Some({origin}) => Some(origin)
                  | None => None
                  };
                let nextOrigin =
                  switch (state.ws->Belt.Array.get(i + 1)) {
                  | Some({origin}) => Some(origin)
                  | None => None
                  };

                <Bubble
                  displayTime={state.displayTime}
                  key={translation.timestamp->string_of_float}
                  surroundingOrigins=(previousOrigin, nextOrigin)
                  translation
                  toggleTime={_ => send(ToggleTime(translation.timestamp))}
                />;
              })
            ->ReasonReact.array}
         </ul>
       }}
    </>;
  },
};
