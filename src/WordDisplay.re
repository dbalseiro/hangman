let rec list_of_string = s =>
  switch (s) {
  | "" => []
  | _ => [s.[0], ...list_of_string(String.sub(s, 1, String.length(s) - 1))]
  };

let style =
  ReactDOMRe.Style.make(
    ~width="50%",
    ~marginLeft="auto",
    ~marginRight="auto",
    ~marginTop="20px",
    ~fontWeight="bold",
    ~textTransform="uppercase",
    ~color="purple",
    (),
  );

let component = ReasonReact.statelessComponent("WordDisplay");

let make = (~word: string, ~correctLetters: list(char), _) => {
  ...component,
  render: _self =>
    <table style>
      <tr>
        {list_of_string(word)
         |> List.map(c =>
              <td>
                {(List.mem(c, correctLetters) ? c : '_')
                 |> String.make(1)
                 |> ReasonReact.string}
              </td>
            )
         |> Array.of_list
         |> ReasonReact.array}
      </tr>
    </table>,
};