let component = ReasonReact.statelessComponent(__MODULE__);

module Style = {
  open Emotion;

  let flag = [%css
    [
      alignItems(`center),
      backgroundColor(`hsl((228, 12, 80))),
      borderRadius(`pct(100.0)),
      display(`flex),
      fontSize(`px(28)),
      height(`px(45)),
      justifyContent(`center),
      marginRight(`px(15)),
      width(`px(45)),
    ]
  ];

  let flagMe = [%css [backgroundColor(`hsl((210, 100, 72)))]];

  let flagInner = [%css [position(`relative), top(`px(2))]];
};

let make = (~origin: Origin.t, ~language: Language.t, _children) => {
  ...component,
  render: _self => {
    <div
      className={Cx.merge([|
        Style.flag,
        switch (origin) {
        | Me => Style.flagMe
        | Other => ""
        },
      |])}>
      <div className=Style.flagInner>
        {(
           switch (language) {
           | English => {js|🇬🇧|js}
           | German => {js|🇩🇪|js}
           | Spanish => {js|🇪🇸|js}
           | French => {js|🇫🇷|js}
           | Chinese => {js|🇨🇳|js}
           | Russian => {js|🇷🇺|js}
           | Romanian => {js|🇷🇴|js}
           | Swedish => {js|🇸🇪|js}
           | _ => ""
           }
         )
         |> Utils.str}
      </div>
    </div>;
  },
};
