type state = {ws: array(WebSocket.t)};

type action =
  | UpdateTranslation(WebSocket.t);

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {ws: [||]},

  didMount: self => {
    WebSocket.(
      socket->listen("message", data =>
        self.send(UpdateTranslation(data->Decode.message->Decode.response))
      )
    )
    |> ignore;
  },

  reducer: (action, state) => {
    switch (action) {
    | UpdateTranslation(ws) =>
      ReasonReact.Update({ws: [|ws|]->Belt.Array.concat(state.ws)})
    };
  },

  render: ({state}) => {
    <>
      <Header />
      {switch (state.ws->Belt.Array.length) {
       | 0 => <EmptyState />
       | _ =>
         <ul className=AppStyle.translations id="list">
           {state.ws
            ->Belt.Array.mapWithIndex((i, translation) => {
                let previousOrigin =
                  switch (state.ws->Belt.Array.get(i - 1)) {
                  | Some({origin}) => Some(origin)
                  | None => None
                  };
                let nextOrigin =
                  switch (state.ws->Belt.Array.get(i + 1)) {
                  | Some({origin}) => Some(origin)
                  | None => None
                  };

                <Bubble
                  key={translation.timestamp->string_of_int}
                  surroundingOrigins=(previousOrigin, nextOrigin)
                  translation
                />;
              })
            ->ReasonReact.array}
         </ul>
       }}
    </>;
  },
};
