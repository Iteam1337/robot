let component = ReasonReact.statelessComponent(__MODULE__);

module Style = {
  open Emotion;

  let bubble = [%css
    [
      backgroundColor(`hex("e5e4ea")),
      borderRadius(`px(20)),
      flexGrow(1.0),
      padding2(`px(10), `px(20)),
      select(":not(:last-child)", [marginBottom(`px(10))]),
    ]
  ];

  let translations = [%css [alignItems(`center), display(`flex)]];

  let transcription = [%css
    [
      fontSize(`px(18)),
      fontWeight(400),
      marginTop(`px(20)),
      maxWidth(`pct(80.0)),
    ]
  ];
};

let make = (~translation: WebSocket.Translation.t, ~transcription, _children) => {
  ...component,
  render: _self => {
    <div className=Style.bubble>
      <div className=Style.translations>
        <Flag language={translation.language} />
        translation.text->Utils.str
      </div>
      <div className=Style.transcription> transcription->Utils.str </div>
    </div>;
  },
};
