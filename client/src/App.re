type state = {ws: array(WebSocket.t)};

type action =
  | UpdateTranslation(WebSocket.t);

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {ws: [||]},

  didMount: self => {
    WebSocket.(
      socket->listen("message", data =>
        self.send(UpdateTranslation(data->Decode.message->Decode.response))
      )
    );
  },

  reducer: (action, state) => {
    switch (action) {
    | UpdateTranslation(ws) =>
      ReasonReact.Update({ws: [|ws|]->Belt.Array.concat(state.ws)})
    };
  },

  render: ({state}) => {
    <>
      <header className=AppStyle.header>
        <div className=AppStyle.logo> {js|🤖|js}->Utils.str </div>
      </header>
      {switch (state.ws->Belt.Array.length) {
       | 0 => <EmptyState />
       | _ =>
         <ul className=AppStyle.translations id="list">
           {state.ws
            ->Belt.Array.map(translation =>
                <Bubble
                  key={translation.timestamp->string_of_int}
                  translation
                />
              )
            ->ReasonReact.array}
         </ul>
       }}
    </>;
  },
};
