let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~onChange, ~options, ~value, _children) => {
  ...component,
  render: _self => {
    <select onChange={e => onChange(e->ReactEvent.Form.target##value)} value>
      <option value=""> "Select a language"->ReasonReact.string </option>
      {options
       ->Belt.Array.map(value =>
           <option key=value value> value->ReasonReact.string </option>
         )
       ->ReasonReact.array}
    </select>;
  },
};
