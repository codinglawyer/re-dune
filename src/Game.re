type env =
  | Sand
  | Ore
  | HighOre
  | Rocks
  | Mountains;

let getEnv = num =>
  switch (num) {
  | 1 => Sand
  | 2 => Rocks
  | _ => Mountains
  };

let createBoard = (~height, ~width) =>
  Array.make_matrix(height, width, Sand);

let randomizeBoard = board =>
  Array.map(row => Array.map(_field => getEnv(Random.int(4)), row), board);

let playingBoard =
  createBoard(~height=40, ~width=40) |> randomizeBoard;

let getEnvClass = env =>
  switch (env) {
  | Sand => "sand"
  | Ore => "ore"
  | HighOre => "highOre"
  | Rocks => "rocks"
  | Mountains => "mountains"
  };

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
                <div key=(string_of_int(i)) className="row">
                  (
                    ReasonReact.array(
                      Array.mapi(
                        (ind, env) =>
                          <div
                            key=(string_of_int(ind))
                            className=((env |> getEnvClass) ++ " field")
                          />,
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