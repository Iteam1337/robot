open Emotion;

let wrap = [%css [padding(`px(40))]];

let logo = [%css [fontSize(`px(60))]];

let header = [%css
  [
    alignItems(`center),
    display(`flex),
    justifyContent(`center),
    left(`px(0)),
    padding(`px(20)),
    position(`fixed),
    right(`px(0)),
    top(`px(0)),
  ]
];

let translate = [%css
  [
    alignItems(`center),
    display(`flex),
    flexDirection(`column),
    height(`calc((`sub, `vh(100.0), `px(80)))),
    justifyContent(`center),
  ]
];

let translation = [%css
  [
    alignItems(`center),
    display(`flex),
    flexDirection(`column),
    fontSize(`px(40)),
    maxWidth(`vw(50.0)),
    textAlign(`center),
    select(":not(:first-child)", [fontSize(`px(60)), opacity(0.5)]),
  ]
];

let spoken = [%css
  [
    color(Theme.Colors.secondary),
    fontSize(`px(18)),
    fontWeight(400),
    marginTop(`px(20)),
    maxWidth(`pct(80.0)),
  ]
];

let response = [%css
  [
    color(Theme.Colors.primary),
    display(`flex),
    flexGrow(1.0),
    fontWeight(700),
    marginBottom(`px(10)),
  ]
];

let flag = [%css [marginRight(`px(30))]];

let emptyState = [%css [color(Theme.Colors.secondary), fontSize(`px(60))]];
