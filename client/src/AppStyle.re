open Emotion;

let logo = [%css [fontSize(`px(60))]];

let header = [%css
  [
    alignItems(`center),
    display(`flex),
    justifyContent(`center),
    padding(`px(20)),
  ]
];

let translations = [%css
  [
    padding(`px(20)),
    display(`inlineFlex),
    flexDirection(`column),
    overflow(`scroll),
    width(`pct(100.0)),
  ]
];

let translation = [%css
  [
    color(`hex("030305")),
    fontSize(`px(24)),
    marginBottom(`px(20)),
    width(`pct(50.0)),
  ]
];

let spoken = [%css
  [
    fontSize(`px(18)),
    fontWeight(400),
    marginTop(`px(20)),
    maxWidth(`pct(80.0)),
  ]
];

let flag = [%css [marginRight(`px(20))]];

let emptyState = [%css [color(Theme.Colors.secondary), fontSize(`px(60))]];
