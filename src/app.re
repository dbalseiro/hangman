[%bs.raw {|require('./app.css')|}];

let randomWord = () => {
  let words = [|"reason", "awesome", "javascript", "nomore"|];

  Js.Date.make() |> Js.Date.getSeconds |> int_of_float |> Random.init;
  words |> Array.length |> Random.int |> Array.get(words);
};

type gameState =
  | GameWon
  | GameLost
  | GamePlaying;

type state = {
  hangState: Hangman.hangState,
  availableLetters: list(char),
  correctLetters: list(char),
  word: string,
  gameState,
};

let initialState = _ => {
  hangState: Hangman.HangedNone,
  availableLetters:
    Belt.List.makeBy(26, i => char_of_int(int_of_char('a') + i)),
  correctLetters: [],
  word: randomWord(),
  gameState: GamePlaying,
};

type action =
  | Guess(char)
  | Correct(char)
  | Miss(char)
  | Won
  | Lost
  | Refresh;

let reducer = (action, state) =>
  switch (action) {
  | Guess(c) =>
    ReasonReact.SideEffects(
      self =>
        (String.contains(state.word, c) ? Correct(c) : Miss(c)) |> self.send,
    )
  | Correct(c) =>
    ReasonReact.UpdateWithSideEffects(
      {
        ...state,
        correctLetters: [c, ...state.correctLetters],
        availableLetters: state.availableLetters |> List.filter((!=)(c)),
      },
      self =>
        self.state.word
        |> WordDisplay.list_of_string
        |> List.for_all(c => List.mem(c, self.state.correctLetters)) ?
          self.send(Won) : (),
    )
  | Miss(c) =>
    ReasonReact.UpdateWithSideEffects(
      {
        ...state,
        hangState: Hangman.next_state(state.hangState),
        availableLetters: state.availableLetters |> List.filter((!=)(c)),
      },
      self =>
        switch (self.state.hangState) {
        | Hangman.HangedRightLeg => self.send(Lost)
        | _ => ()
        },
    )
  | Won => ReasonReact.Update({...state, gameState: GameWon})
  | Lost => ReasonReact.Update({...state, gameState: GameLost})
  | Refresh => ReasonReact.Update(initialState())
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState,
  reducer,
  render: self =>
    <div className="App">
      <div> <Hangman hangState={self.state.hangState} /> </div>
      <div>
        {switch (self.state.gameState) {
         | GameLost =>
           <button
             onClick={_ => self.send(Refresh)} className="btn btn-danger">
             {ReasonReact.string("You Lost!!")}
           </button>

         | GameWon =>
           <button
             onClick={_ => self.send(Refresh)} className="btn btn-success">
             {ReasonReact.string("You Won!!")}
           </button>
         | GamePlaying =>
           <Guesser
             onClickLetter={c => self.send(Guess(c))}
             availableLetters={self.state.availableLetters}
           />
         }}
      </div>
      <div>
        <WordDisplay
          word={self.state.word}
          correctLetters={self.state.correctLetters}
        />
      </div>
    </div>,
};
