let component = ReasonReact.statelessComponent(__MODULE__);

module Style = {
  open Emotion;

  let bubble = [%css
    [
      backgroundColor(`hex("e5e4ea")),
      borderRadius(`px(20)),
      maxWidth(`pct(50.0)),
      padding2(`px(10), `px(20)),
      select(":not(:last-child)", [marginBottom(`px(10))]),
    ]
  ];

  let translations = [%css
    [
      display(`grid),
      gridTemplateColumns(`list([`repeat((`n(2), [`fr(1.0)]))])),
      gridColumnGap(`px(10)),
      gridRowGap(`px(5)),
    ]
  ];

  let translation = [%css [alignItems(`center), display(`flex)]];

  let transcription = [%css
    [
      fontSize(`px(18)),
      fontWeight(400),
      marginTop(`px(20)),
      maxWidth(`pct(80.0)),
    ]
  ];
};

let make = (~translation: WebSocket.t, _children) => {
  ...component,
  render: _self => {
    <li className=Style.bubble>
      <div className=Style.translations>
        {translation.translations
         ->Belt.Array.map(translation =>
             <div className=Style.translation key={translation.rawLanguage}>
               <Flag language={translation.language} />
               translation.text->Utils.str
             </div>
           )
         ->ReasonReact.array}
      </div>
      <div className=Style.transcription>
        translation.transcription->Utils.str
      </div>
    </li>;
  },
};
