let component = ReasonReact.statelessComponent(__MODULE__);

let make = _children => {
  ...component,
  render: _self => {
    <div className={Cx.merge([|AppStyle.translate, AppStyle.emptyState|])}>
      "Say something nice!"->Utils.str
    </div>;
  },
};
