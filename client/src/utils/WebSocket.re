type ws;

type t = {
  origin: Origin.t,
  timestamp: float,
  translations: array(Translation.t),
  transcription: string,
};

[@bs.new] external ws: string => ws = "WebSocket";

[@bs.send]
external listen: (ws, string, Js.Json.t => unit) => 'a = "addEventListener";

module Decode = {
  let response = json =>
    Json.Decode.{
      origin: json |> field("origin", string) |> Origin.decode,
      timestamp: json |> field("timestamp", Json.Decode.float),
      translations: json |> field("translations", array(Translation.decode)),
      transcription: json |> field("transcription", string),
    };

  let message = json =>
    Json.Decode.(json |> field("data", string) |> Js.Json.parseExn);
};

let socket = ws("ws://localhost:8080");
