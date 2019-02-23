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
