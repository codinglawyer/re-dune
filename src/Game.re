type env =
  | Sand
  | Ore
  | HighOre
  | Rocks
  | Mountains
  | Empty;

let getEnvClass = env =>
  switch (env) {
  | Sand => "sand"
  | Ore => "ore"
  | HighOre => "highOre"
  | Rocks => "rocks"
  | Mountains => "mountains"
  };

type playingBoard = array(array(env));

let addRocks = (num: int, _field) =>
  switch (num) {
  | 1 => Rocks
  | _ => Sand
  };

let addOre = (num: int, field) =>
  switch (field) {
  | Sand =>
    switch (num) {
    | 1 => Ore
    | _ => Sand
    }
  | _ => field
  };

let createSandBoard = (~width: int, ~height: int) =>
  Array.make_matrix(width, height, Sand);

let randomizeBoard = (fn, board: playingBoard) =>
  Array.map(
    row => Array.map(field => fn(Random.int(3), field), row),
    board,
  );

let getFieldType = ((y: int, x: int), board: playingBoard) =>
  switch (y, x) {
  | _ when y < 0 || y >= Array.length(board) => Sand
  | _ when x < 0 || x >= Array.length(board[0]) => Sand
  | _ => board[y][x]
  };

let countNearbyRocks = (sum, field) =>
  switch (field) {
  | Sand => sum
  | Rocks => sum + 1
  };

let countNearbyOre = (sum, field) =>
  switch (field) {
  | Ore => sum + 1
  | _ => sum
  };

let countNeighbours = ((x, y), board, countFn, getFieldFn) =>
  List.fold_left(
    (sum, (diffX, diffY)) => {
      let neighbourY = y + diffY;
      let neighbourX = x + diffX;
      let field = getFieldFn((neighbourX, neighbourY), board);
      countFn(sum, field);
    },
    0,
    [
      ((-1), (-1)),
      ((-1), 0),
      ((-1), 1),
      (0, (-1)),
      (0, 1),
      (1, (-1)),
      (1, 0),
      (1, 1),
    ],
  );

let rockBoard = board =>
  Array.mapi(
    (x, row) =>
      Array.mapi(
        (y, field) => {
          let neighbours =
            countNeighbours((x, y), board, countNearbyRocks, getFieldType);
          switch (neighbours) {
          | _ when neighbours < 2 => Sand
          | _ when neighbours < 4 => field
          | _ => Rocks
          };
        },
        row,
      ),
    board,
  );

let playingBoard =
  createSandBoard(~width=20, ~height=15) |> randomizeBoard(addRocks);

let rocksBoard = rockBoard(playingBoard);

let ores = (board: playingBoard) => randomizeBoard(addOre, board);

let mapWithOre = ores(rocksBoard);

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
              mapWithOre,
            ),
          )
        )
      </div>
    </div>,
};