let component = ReasonReact.statelessComponent(__MODULE__);

module Style = {
  open Emotion;

  let wrap = [%css
    [
      color(`hsl((0, 0, 70))),
      fontSize(`px(60)),
      paddingTop(`px(20)),
      position(`fixed),
      textAlign(`center),
      top(`pct(50.0)),
      transform(`translateY(`pct(-50.0))),
      width(`pct(100.0)),
    ]
  ];
};

let make = _children => {
  ...component,
  render: _self => {
    <div className=Style.wrap> "Say something nice!"->Utils.str </div>;
  },
};
