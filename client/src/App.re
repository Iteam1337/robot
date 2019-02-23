type state = {
  displayTime: int,
  ws: array(WebSocket.t),
};

type action =
  | ToggleTime(int)
  | UpdateTranslation(WebSocket.t);

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {displayTime: 0, ws: [||]},

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
    | ToggleTime(displayTime) =>
      ReasonReact.Update({
        ...state,
        displayTime: displayTime === state.displayTime ? 0 : displayTime,
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
      <Header />
      {switch (state.ws->Belt.Array.length) {
       | 0 => <EmptyState />
       | _ =>
         <ul className=AppStyle.translations id="list">
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
                  key={translation.timestamp->string_of_int}
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
