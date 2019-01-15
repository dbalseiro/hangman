[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <div className="App"> (ReasonReact.string("Hola Mundo")) </div>,
};
