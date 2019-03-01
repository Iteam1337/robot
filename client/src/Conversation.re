let component = ReasonReact.statelessComponent(__MODULE__);

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

let make =
    (~translations: array(WebSocket.t), ~displayTime, ~toggleTime, _children) => {
  ...component,
  render: _self => {
    <ul className=Style.translations>
      {translations
       ->Belt.Array.mapWithIndex((i, translation) => {
           let previousOrigin =
             switch (translations->Belt.Array.get(i - 1)) {
             | Some({origin}) => Some(origin)
             | None => None
             };
           let nextOrigin =
             switch (translations->Belt.Array.get(i + 1)) {
             | Some({origin}) => Some(origin)
             | None => None
             };

           <Bubble
             displayTime
             key={translation.timestamp->string_of_float}
             surroundingOrigins=(previousOrigin, nextOrigin)
             translation
             toggleTime={_ => toggleTime(translation)}
           />;
         })
       ->ReasonReact.array}
    </ul>;
  },
};
