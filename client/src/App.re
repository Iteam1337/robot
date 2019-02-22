type state = {ws: array(WebSocket.t)};

type action =
  | UpdateTranslation(WebSocket.t);

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {ws: [||]},

  didMount: self => {
    /* self.send( */
    /*   UpdateTranslation({ */
    /*     origin: WebSocket.Origin.Me, */
    /*     transcription: "lorem aepgroj aepgj aepojgpaeo gpoaegjrpaegrjpaejgrpaerj */
           /*       gpjaepgrj aepjgrpaejgpj epj gpaejgrpj apegjp", */
    /*     translations: [| */
    /*       {language: English, text: "Hello", rawLanguage: "en"}, */
    /*       {language: Spanish, text: "Hola", rawLanguage: "es"}, */
    /*       {language: German, text: "Hallo", rawLanguage: "ge"}, */
    /*       {language: French, text: "Bonjour", rawLanguage: "fr"}, */
    /*       {language: Chinese, text: {js|你好|js}, rawLanguage: "ch"}, */
    /*     |], */
    /*     timestamp: 0, */
    /*   }), */
    /* ); */
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
                <div
                  className=AppStyle.translation
                  key={t.timestamp->string_of_int}>
                  {t.translations
                   ->Belt.Array.map(({language, rawLanguage, text}) =>
                       <div className=AppStyle.response key=rawLanguage>
                         <div className=AppStyle.flag>
                           {(
                              switch (language) {
                              | English => {js|🇬🇧|js}
                              | German => {js|🇩🇪|js}
                              | Spanish => {js|🇪🇸|js}
                              | French => {js|🇫🇷|js}
                              | Chinese => {js|🇨🇳|js}
                              | _ => ""
                              }
                            )
                            |> Utils.str}
                         </div>
                         text->Utils.str
                       </div>
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
