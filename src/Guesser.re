let component = ReasonReact.statelessComponent("Guesser");

let make = (~onClickLetter, ~availableLetters: list(char), _) => {
  ...component,
  render: _self =>
    availableLetters
    |> List.map(c =>
         <button className="btn btn-default" onClick={_ => onClickLetter(c)}>
           {ReasonReact.string(String.make(1, c))}
         </button>
       )
    |> Array.of_list
    |> ReasonReact.array,
};