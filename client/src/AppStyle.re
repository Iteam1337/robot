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

let spoken = [%css
  [
    color(Theme.Colors.secondary),
    fontSize(`px(24)),
    fontWeight(600),
    marginTop(`px(20)),
  ]
];

let response = [%css
  [color(Theme.Colors.primary), fontSize(`px(140)), fontWeight(700)]
];

let emptyState = [%css [color(Theme.Colors.secondary), fontSize(`px(60))]];
