let s = ReasonReact.string;

type state = {scrollPosition: int};

type action =
  | Scroll(int);

let component = ReasonReact.reducerComponent(__MODULE__);

module Style = {
  open Emotion;

  let header = [%css
    [
      alignItems(`center),
      backgroundColor(`rgba((255, 255, 255, 0.9))),
      display(`flex),
      fontSize(`px(60)),
      justifyContent(`spaceBetween),
      left(`zero),
      padding(`px(20)),
      position(`fixed),
      right(`zero),
      top(`zero),
      transitionProperty("font-size, padding"),
      transitionDuration(`ms(300)),
      transitionTimingFunction(`easeInOut),
      zIndex(1),
    ]
  ];

  let headerScrolled = [%css [fontSize(`px(24)), padding(`px(10))]];

  let mode = [%css [alignItems(`center), display(`flex)]];
};

let make = (~currentDisplayMode, ~changeDisplayMode, _children) => {
  ...component,
  initialState: () => {scrollPosition: 0},

  didMount: self => {
    Webapi.Dom.(
      Window.addEventListener(
        "scroll",
        _ => {
          let windowScrollY = [%raw "window.scrollY"];
          self.send(Scroll(windowScrollY));
        },
        window,
      )
    );
  },

  reducer: (action, _state) => {
    switch (action) {
    | Scroll(scrollPosition) =>
      ReasonReact.Update({scrollPosition: scrollPosition})
    };
  },

  render: ({state}) =>
    <header
      className={Cx.merge([|
        Style.header,
        state.scrollPosition > 0 ? Style.headerScrolled : "",
      |])}>
      <div> {js|🤖|js}->Utils.str </div>
      <div className=Style.mode>
        <Button
          active={currentDisplayMode === Mode.Conversation}
          onClick={_ => changeDisplayMode(Mode.Conversation)}>
          {s("Conversation")}
        </Button>
        <Button
          active={currentDisplayMode === Mode.Presentation}
          onClick={_ => changeDisplayMode(Mode.Presentation)}>
          {s("Presentation")}
        </Button>
      </div>
    </header>,
};
