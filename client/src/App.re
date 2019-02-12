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
let languages = [|"en-US", "sv-SE"|];

let make = _children => {
  ...component,

  initialState: () => {
    input: "",
    output: "",
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
          options=languages
          value={state.input}
        />
        <Dropdown
          onChange={v => send(UpdateOutput(v))}
          options=languages
          value={state.output}
        />
      </div>
      <div className=AppStyle.translate>
        <div className=AppStyle.response>
          state.translation.translation->ReasonReact.string
        </div>
        <div className=AppStyle.spoken>
          state.translation.transcription->ReasonReact.string
        </div>
      </div>
    </div>;
  },
};
