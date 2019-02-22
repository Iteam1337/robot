type state = {ws: WebSocket.t};

type action =
  | UpdateTranslation(WebSocket.t);

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {
    ws: {
      origin: "",
      timestamp: 0,
      translations: [||],
      transcription: "",
    },
  },

  didMount: self => {
    WebSocket.(
      socket->listen("message", data =>
        self.send(UpdateTranslation(data->Decode.message->Decode.response))
      )
    );
  },

  reducer: (action, _state) => {
    switch (action) {
    | UpdateTranslation(ws) => ReasonReact.Update({ws: ws})
    };
  },

  render: ({state: {ws}}) => {
    <div className=AppStyle.wrap>
      <header className=AppStyle.header>
        <div className=AppStyle.logo> {js|🤖|js}->Utils.str </div>
      </header>
      {switch (ws.transcription->Js.String.length) {
       | 0 => <EmptyState />
       | _ =>
         <div className=AppStyle.translate>
           {ws.translations
            ->Belt.Array.map(({text}) =>
                <div className=AppStyle.response> text->Utils.str </div>
              )
            ->ReasonReact.array}
           <div className=AppStyle.spoken> ws.transcription->Utils.str </div>
         </div>
       }}
    </div>;
  },
};
