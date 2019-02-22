type ws;

module Translation = {
  type t = {
    language: string,
    text: string,
  };

  let decode = json =>
    Json.Decode.{
      language: json |> field("language", string),
      text: json |> field("text", string),
    };
};

type t = {
  origin: string,
  timestamp: int,
  translations: array(Translation.t),
  transcription: string,
};

[@bs.new] external ws: string => ws = "WebSocket";

[@bs.send]
external listen: (ws, string, Js.Json.t => unit) => 'a = "addEventListener";

module Decode = {
  let response = json =>
    Json.Decode.{
      origin: json |> field("origin", string),
      timestamp: json |> field("timestamp", int),
      translations: json |> field("translations", array(Translation.decode)),
      transcription: json |> field("transcription", string),
    };

  let message = json =>
    Json.Decode.(json |> field("data", string) |> Js.Json.parseExn);
};

let socket = ws("ws://localhost:8080");
