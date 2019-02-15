type state = {
  input: string,
  output: string,
  translation: WebSocket.translation,
};

type action =
  | UpdateTranslation(WebSocket.translation)
  | UpdateInput(string)
  | UpdateOutput(string);

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {
    input: "sv-SE",
    output: "en-US",
    translation: {
      timestamp: 0,
      translation: "",
      transcription: "",
    },
  },

  didMount: self => {
    WebSocket.(
      socket->listen("message", data =>
        self.send(
          UpdateTranslation(data->Decode.message->Decode.translation),
        )
      )
    );
  },

  reducer: (action, state) => {
    switch (action) {
    | UpdateTranslation(translation) =>
      ReasonReact.Update({...state, translation})
    | UpdateInput(input) => ReasonReact.Update({...state, input})
    | UpdateOutput(output) => ReasonReact.Update({...state, output})
    };
  },

  render: ({send, state}) => {
    <div className=AppStyle.wrap>
      <div className=AppStyle.dropdowns>
        <Dropdown
          onChange={v => send(UpdateInput(v))}
          options=Languages.supportedLanguages
          placeholder="Select input language"
          value={state.input}
        />
        <Dropdown
          onChange={v => send(UpdateOutput(v))}
          options=Languages.supportedLanguages
          placeholder="Select output language"
          value={state.output}
        />
      </div>
      {switch (state.translation.translation->Js.String.length) {
       | 0 =>
         <div
           className={Cx.merge([|AppStyle.translate, AppStyle.emptyState|])}>
           {js|Say something nice! 🤖|js}->ReasonReact.string
         </div>
       | _ =>
         <div className=AppStyle.translate>
           <div className=AppStyle.response>
             state.translation.translation->ReasonReact.string
           </div>
           <div className=AppStyle.spoken>
             state.translation.transcription->ReasonReact.string
           </div>
         </div>
       }}
    </div>;
  },
};
