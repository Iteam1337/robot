type ws;

module Language = {
  type t =
    | Swedish
    | English
    | German
    | French
    | Spanish
    | Chinese
    | Russian
    | Romanian
    | UnknownLanguage;

  let decode = input =>
    switch (input) {
    | "sv" => Swedish
    | "en" => English
    | "de" => German
    | "fr" => French
    | "es" => Spanish
    | "ru" => Russian
    | "ro" => Romanian
    | "zh" => Chinese
    | _ => UnknownLanguage
    };
};

module Translation = {
  type t = {
    language: Language.t,
    rawLanguage: string,
    text: string,
  };

  let decode = json =>
    Json.Decode.{
      language: json |> field("language", string) |> Language.decode,
      rawLanguage: json |> field("language", string),
      text: json |> field("text", string),
    };
};

module Origin = {
  type t =
    | Me
    | Other;

  let decode = input =>
    switch (input) {
    | "me" => Me
    | _ => Other
    };
};

type t = {
  origin: Origin.t,
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
      origin: json |> field("origin", string) |> Origin.decode,
      timestamp: json |> field("timestamp", int),
      translations: json |> field("translations", array(Translation.decode)),
      transcription: json |> field("transcription", string),
    };

  let message = json =>
    Json.Decode.(json |> field("data", string) |> Js.Json.parseExn);
};

let socket = ws("ws://localhost:8080");
