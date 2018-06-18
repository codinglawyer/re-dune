type env =
  | Sand
  | Spice
  | HighSpice
  | Rocks
  | Mountains;

let createPlayingBoard = (~height, ~width) =>
  Array.make_matrix(height, width, "field");

let playingBoard = createPlayingBoard(~height=40, ~width=40);

let component = ReasonReact.statelessComponent("Game");
let make = _children => {
  ...component,
  render: _self =>
    <div>
      <div className="game">
        (
          ReasonReact.array(
            Array.mapi(
              (i, row) =>
                <div key=(string_of_int(i)) className="field">
                  (
                    ReasonReact.array(
                      Array.mapi(
                        (ind, _field) =>
                          <div key=(string_of_int(ind)) className="field" />,
                        row,
                      ),
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