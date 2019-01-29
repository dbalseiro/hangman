let component = ReasonReact.statelessComponent("Hangman");

let make = (_) => {
  ...component,
  render: _self => <img width="200" src="./Hangman-0.png" />,
};
