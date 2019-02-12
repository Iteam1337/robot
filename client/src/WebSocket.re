type ws;

type translation = {
  timestamp: int,
  translation: string,
  transcription: string,
};

[@bs.new] external ws: string => ws = "WebSocket";

[@bs.send]
external listen: (ws, string, Js.Json.t => unit) => 'a = "addEventListener";

module Decode = {
  let translation = json =>
    Json.Decode.{
      timestamp: json |> field("timestamp", int),
      translation: json |> field("translation", string),
      transcription: json |> field("transcription", string),
    };

  let message = json =>
    Json.Decode.(json |> field("data", string) |> Js.Json.parseExn);
};

let socket = ws("ws://localhost:8080");
