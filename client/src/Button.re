let s = ReasonReact.string;

let component = ReasonReact.statelessComponent(__MODULE__);

module Style = {
  open Emotion;

  let button = [%css
    [
      borderWidth(`zero),
      borderRadius(`px(30)),
      cursor(`pointer),
      fontSize(`px(16)),
      padding2(`px(10), `px(20)),
      select(":not(:last-child)", [marginRight(`px(20))]),
    ]
  ];

  let active = [%css
    [backgroundColor(`hex("0c84fe")), color(`hex("dceeff"))]
  ];
};

let make = (~active, ~onClick, children) => {
  ...component,
  render: _self => {
    <button
      className={Cx.merge([|Style.button, active ? Style.active : ""|])}
      onClick>
      ...children
    </button>;
  },
};
