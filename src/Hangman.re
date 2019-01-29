type hangState =
  | HangedNone
  | HangedHead
  | HangedBody
  | HangedLeftArm
  | HangedRightArm
  | HangedLeftLeg
  | HangedRightLeg;

let filename_of_hanged = hangState =>
  switch (hangState) {
  | HangedNone => "./Hangman-0.png"
  | HangedHead => "./Hangman-1.png"
  | HangedBody => "./Hangman-2.png"
  | HangedLeftArm => "./Hangman-3.png"
  | HangedRightArm => "./Hangman-4.png"
  | HangedLeftLeg => "./Hangman-5.png"
  | HangedRightLeg => "./Hangman-6.png"
  };

let next_state = hangState =>
  switch (hangState) {
  | HangedNone => HangedHead
  | HangedHead => HangedBody
  | HangedBody => HangedLeftArm
  | HangedLeftArm => HangedRightArm
  | HangedRightArm => HangedLeftLeg
  | HangedLeftLeg => HangedRightLeg
  | HangedRightLeg => HangedHead
  };

let component = ReasonReact.statelessComponent("Hangman");

let make = (~hangState, _) => {
  ...component,
  render: _self => <img width="200" src={filename_of_hanged(hangState)} />,
};