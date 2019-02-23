type t =
  | Me
  | Other;

let decode = input =>
  switch (input) {
  | "me" => Me
  | _ => Other
  };
