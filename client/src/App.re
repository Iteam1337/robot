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
let socket = WebSocket.ws("ws://localhost:8080");

let make = _children => {
  ...component,

  didMount: self => {
    WebSocket.(
      socket->listen("message", data => {
        let message = data->Decode.message;
        let translation = message->Decode.translation;

        self.send(UpdateTranslation(translation));
      })
    );
  },

  initialState: () => {
    input: "",
    output: "",
    translation: {
      timestamp: 0,
      translation: "",
      transcription: "",
    },
  },

  reducer: (action, state) => {
    switch (action) {
    | UpdateTranslation(translation) =>
      ReasonReact.Update({...state, translation})
    | UpdateInput(input) => ReasonReact.Update({...state, input})
    | UpdateOutput(input) => ReasonReact.Update({...state, input})
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
      <ul className=AppStyle.translate>
        <li key={state.translation.timestamp->string_of_int}>
          <div className=AppStyle.response>
            state.translation.translation->ReasonReact.string
          </div>
          <div className=AppStyle.spoken>
            state.translation.transcription->ReasonReact.string
          </div>
        </li>
      </ul>
    </div>;
  },
};
