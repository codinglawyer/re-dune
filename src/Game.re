type env =
  | Sand
  | Spice
  | HighSpice
  | Rocks
  | Mountains;

let createPlayingBoard = (width, height) =>
  Array.make_matrix(height, width, "field");

let playingBoard = createPlayingBoard(40, 40);

let component = ReasonReact.statelessComponent("Game");
let make = _children => {
  ...component,
  render: _self =>
    <div>
      <div className="game">
        (
          ReasonReact.array(
            Array.map(
              row =>
                <div className="field">
                  (
                    ReasonReact.array(
                      Array.map(_field => <div className="field" />, row),
                    )
                  )
                </div>,
              playingBoard,
            ),
          )
        )
      </div>
    </div>,
};