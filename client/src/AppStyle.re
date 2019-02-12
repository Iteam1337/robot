open Emotion;

let wrap = [%css [padding(`px(40))]];

let dropdowns = [%css [position(`fixed), right(`px(40)), top(`px(40))]];

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
    color(`hsl((175, 34, 10))),
    fontSize(`px(21)),
    fontWeight(600),
    marginTop(`px(10)),
  ]
];

let response = [%css
  [color(`hsl((175, 34, 50))), fontSize(`px(100)), fontWeight(700)]
];
