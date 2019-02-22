let component = ReasonReact.statelessComponent(__MODULE__);

module Style = {
  open Emotion;

  let fadeIn =
    keyframes([
      (0, [transform(`scale(0.9))]),
      (100, [transform(`scale(1.0))]),
    ]);

  let bubble = [%css
    [
      animationName(fadeIn),
      animationDuration(`ms(300)),
      animationIterationCount(`i(1)),
      backgroundColor(`hex("e5e4ea")),
      borderRadius(`px(30)),
      boxShadows([
        (`zero, `px(4), `px(6), `zero, `rgba((0, 6, 56, 0.1)), false),
        (`zero, `px(4), `px(40), `zero, `rgba((0, 0, 0, 0.05)), false),
      ]),
      color(`hsl((248, 12, 45))),
      fontSize(`px(14)),
      padding2(`px(20), `px(30)),
      position(`relative),
      width(`pct(100.0)),
      select(":not(:last-child)", [marginBottom(`px(30))]),
      media("(min-width: 768px)", [width(`pct(48.0))]),
    ]
  ];

  let bubbleMe = [%css
    [
      alignSelf(`flexEnd),
      backgroundColor(`hex("0c84fe")),
      color(`hex("dceeff")),
    ]
  ];

  let otherNextIsSame = [%css [borderTopLeftRadius(`px(6))]];
  let otherBothAreSame = [%css
    [
      important(marginBottom(`px(15))),
      borderBottomLeftRadius(`px(6)),
      borderTopLeftRadius(`px(6)),
    ]
  ];
  let otherPreviousIsSame = [%css
    [important(marginBottom(`px(15))), borderBottomLeftRadius(`px(6))]
  ];

  let meNextIsSame = [%css [borderTopRightRadius(`px(6))]];
  let meBothAreSame = [%css
    [
      important(marginBottom(`px(15))),
      borderBottomRightRadius(`px(6)),
      borderTopRightRadius(`px(6)),
    ]
  ];
  let mePreviousIsSame = [%css
    [important(marginBottom(`px(15))), borderBottomRightRadius(`px(6))]
  ];

  let translations = [%css
    [
      display(`grid),
      gridTemplateColumns(`list([`repeat((`n(1), [`fr(1.0)]))])),
      gridColumnGap(`px(10)),
      gridRowGap(`px(10)),
      media(
        "(min-width: 768px)",
        [gridTemplateColumns(`list([`repeat((`n(2), [`fr(1.0)]))]))],
      ),
    ]
  ];

  let translation = [%css [alignItems(`center), display(`flex)]];

  let translationText = [%css
    [flexGrow(1.0), flexShrink(1.0), flexBasis(`zero)]
  ];

  let transcription = [%css
    [
      fontSize(`px(18)),
      fontWeight(400),
      marginTop(`px(20)),
      maxWidth(`pct(80.0)),
    ]
  ];
};

let make =
    (
      ~surroundingOrigins: (
         option(WebSocket.Origin.t),
         option(WebSocket.Origin.t),
       ),
      ~translation: WebSocket.t,
      _children,
    ) => {
  ...component,
  render: _self => {
    <li
      className={Cx.merge([|
        Style.bubble,
        switch (translation.origin) {
        | Me => Style.bubbleMe
        | Other => ""
        },
        switch (translation.origin, surroundingOrigins) {
        | (Other, (Some(Other), Some(Other))) => Style.otherBothAreSame
        | (Other, (Some(Other), _)) => Style.otherNextIsSame
        | (Other, (_, Some(Other))) => Style.otherPreviousIsSame
        | (Me, (Some(Me), Some(Me))) => Style.meBothAreSame
        | (Me, (Some(Me), _)) => Style.meNextIsSame
        | (Me, (_, Some(Me))) => Style.mePreviousIsSame
        | _ => ""
        },
      |])}>
      <div className=Style.translations>
        {translation.translations
         ->Belt.Array.map(t =>
             <div className=Style.translation key={t.rawLanguage}>
               <Flag language={t.language} origin={translation.origin} />
               <div className=Style.translationText> t.text->Utils.str </div>
             </div>
           )
         ->ReasonReact.array}
        <div className=Style.translation>
          <Flag language=Swedish origin={translation.origin} />
          <div className=Style.translationText>
            translation.transcription->Utils.str
          </div>
        </div>
      </div>
    </li>;
  },
};
