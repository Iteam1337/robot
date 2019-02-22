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

  render: ({state: {ws}}) => {
    <div className=AppStyle.wrap>
      <header className=AppStyle.header>
        <div className=AppStyle.logo> {js|🤖|js}->Utils.str </div>
      </header>
      {switch (ws->Belt.Array.length) {
       | 0 => <EmptyState />
       | _ =>
         <div className=AppStyle.translate>
           {ws
            ->Belt.Array.map(t =>
                <div className=AppStyle.translation>
                  {t.translations
                   ->Belt.Array.map(({text}) =>
                       <div className=AppStyle.response> text->Utils.str </div>
                     )
                   ->ReasonReact.array}
                  <div className=AppStyle.spoken>
                    t.transcription->Utils.str
                  </div>
                </div>
              )
            ->ReasonReact.array}
         </div>
       }}
    </div>;
  },
};
