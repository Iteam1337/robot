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
