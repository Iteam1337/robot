[@bs.scope "JSON"] [@bs.val]
external parseToJson: string => Js.Json.t = "parse";

type wsSocket;

type translation = {
  timestamp: int,
  translation: string,
  transcription: string,
};

[@bs.new] external ws: string => wsSocket = "WebSocket";

[@bs.send]
external listen: (wsSocket, string, Js.Json.t => unit) => 'a =
  "addEventListener";

module Decode = {
  let translation = json =>
    Json.Decode.{
      timestamp: json |> field("timestamp", int),
      translation: json |> field("translation", string),
      transcription: json |> field("transcription", string),
    };

  let message = json =>
    Json.Decode.(json |> field("data", string) |> parseToJson);
};
