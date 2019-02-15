let component = ReasonReact.statelessComponent(__MODULE__);

module Style = {
  open Emotion;

  let dropdown = [%css
    [
      appearance(`none),
      backgroundColor(Theme.Colors.primary),
      borderStyle(`none),
      borderRadius(`px(20)),
      color(`hex("fff")),
      fontSize(`px(14)),
      marginLeft(`px(10)),
      padding2(`px(10), `px(20)),
      textAlign(`center),
    ]
  ];
};

let make =
    (
      ~onChange,
      ~options: array(Languages.t),
      ~placeholder,
      ~value,
      _children,
    ) => {
  ...component,
  render: _self => {
    <select
      className=Style.dropdown
      onChange={e => onChange(e->ReactEvent.Form.target##value)}
      value>
      <option value=""> placeholder->ReasonReact.string </option>
      {options
       ->Belt.Array.map(({iso, name}: Languages.t) =>
           <option key=name value=iso> name->ReasonReact.string </option>
         )
       ->ReasonReact.array}
    </select>;
  },
};
