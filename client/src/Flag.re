let component = ReasonReact.statelessComponent(__MODULE__);

module Style = {
  open Emotion;

  let flag = [%css [marginRight(`px(20))]];
};

let make = (~language: WebSocket.Language.t, _children) => {
  ...component,
  render: _self => {
    <div className=Style.flag>
      {(
         switch (language) {
         | English => {js|🇬🇧|js}
         | German => {js|🇩🇪|js}
         | Spanish => {js|🇪🇸|js}
         | French => {js|🇫🇷|js}
         | Chinese => {js|🇨🇳|js}
         | _ => ""
         }
       )
       |> Utils.str}
    </div>;
  },
};
