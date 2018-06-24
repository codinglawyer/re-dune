type env =
  | Sand
  | Ore
  | HighOre
  | Rocks
  | Mountains
  | Empty;

let getEnvClass = (env: env) =>
  switch (env) {
  | Sand => "sand"
  | Ore => "ore"
  | HighOre => "highOre"
  | Rocks => "rocks"
  | Mountains => "mountains"
  | Empty => ""
  };

type playingBoard = array(array(env));

let addRocks = (num: int, field) =>
  switch (num) {
  | 1 => Rocks
  | _ => field
  };

let addOre = (num: int, field) =>
  switch (field) {
  | Sand =>
    switch (num) {
    | 1 => Ore
    | _ => field
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

let countNearbyEnvs = (env, sum, field) => env === field ? sum + 1 : sum;

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

let combineRocks = board =>
  Array.mapi(
    (x, row) =>
      Array.mapi(
        (y, field) => {
          let neighbours =
            countNeighbours(
              (x, y),
              board,
              countNearbyEnvs(Rocks),
              getFieldType,
            );
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

let combineOre = board =>
  Array.mapi(
    (x, row) =>
      Array.mapi(
        (y, field) =>
          switch (field) {
          | Ore =>
            let neighbours =
              countNeighbours(
                (x, y),
                board,
                countNearbyEnvs(Ore),
                getFieldType,
              );
            switch (neighbours) {
            | 1 => Rocks
            | _ => Ore
            };
          | Sand =>
            let neighbours =
              countNeighbours(
                (x, y),
                board,
                countNearbyEnvs(Sand),
                getFieldType,
              );
            switch (neighbours) {
            | 3 => Ore
            | 4 => Ore
            | _ => Sand
            };
          | Rocks =>
            let neighbours =
              countNeighbours(
                (x, y),
                board,
                countNearbyEnvs(Rocks),
                getFieldType,
              );
            switch (neighbours) {
            | 3 => Ore
            | _ => Rocks
            };
          | _ => Empty
          },
        row,
      ),
    board,
  );

let playingBoard =
  createSandBoard(~width=20, ~height=15)
  |> randomizeBoard(addRocks)
  |> combineRocks
  |> randomizeBoard(addOre)
  |> combineOre;

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