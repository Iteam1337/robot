let component = ReasonReact.statelessComponent(__MODULE__);

module Style = {
  open Emotion;

  let time = [%css
    [
      color(`hsl((211, 15, 50))),
      fontSize(`px(14)),
      left(`zero),
      opacity(0.5),
      position(`absolute),
      right(`zero),
      textAlign(`center),
      transforms([`translateY(`px(30))]),
      transitions([
        ("transform", `ms(200), `easeInOut, `zero),
        ("opacity", `ms(200), `easeInOut, `zero),
      ]),
    ]
  ];

  let timeDisplayed = [%css
    [
      opacity(1.0),
      padding(`px(10)),
      paddingTop(`zero),
      position(`relative),
      transforms([`translateY(`zero)]),
    ]
  ];
};

let addLeadingZero = date => {
  switch (date) {
  | x when x < 10. => "0" ++ string_of_int(int_of_float(date))
  | _ => string_of_int(int_of_float(date))
  };
};

let make = (~timestamp, ~displayTime: int, _children) => {
  ...component,
  render: _self => {
    let date = Js.Date.fromFloat(timestamp->float_of_int);

    <div
      className={Cx.merge([|
        Style.time,
        displayTime === timestamp ? Style.timeDisplayed : "",
      |])}>
      {date->Js.Date.getHours->addLeadingZero
       ++ ":"
       ++ date->Js.Date.getMinutes->addLeadingZero
       |> Utils.str}
    </div>;
  },
};
