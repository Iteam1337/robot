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
         <Conversation
           displayTime={state.displayTime}
           toggleTime={translation =>
             send(ToggleTime(translation.timestamp))
           }
           translations={state.ws}
         />
       }}
    </>;
  },
};
