type env =
  | Sand
  | Spice
  | SpiceDune
  | Rock
  | Hill
  | SpiceBloom
  | Empty;

let getEnvClass = (env: env) =>
  switch (env) {
  | Sand => "sand"
  | Spice => "spice"
  | SpiceDune => "spiceDune"
  | Rock => "rock"
  | Hill => "hill"
  | SpiceBloom => "spiceBloom"
  | Empty => ""
  };

type playingBoard = array(array(env));

let addRock = (num: int, field) =>
  switch (num) {
  | 1 => Rock
  | _ => field
  };

let addSpice = (num: int, field) =>
  switch (field) {
  | Sand =>
    switch (num) {
    | 1 => Spice
    | _ => field
    }
  | _ => field
  };

let addHill = (num: int, field) =>
  switch (field) {
  | Rock =>
    switch (num) {
    | 1 => Hill
    | _ => field
    }
  | _ => field
  };

let createSandBoard = (~width: int, ~height: int) =>
  Array.make_matrix(width, height, Sand);

let randomizeBoard = (fn, seed, board: playingBoard) =>
  Array.map(
    row => Array.map(field => fn(Random.int(seed), field), row),
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

let combineRock = board =>
  Array.mapi(
    (x, row) =>
      Array.mapi(
        (y, field) => {
          let neighbours =
            countNeighbours(
              (x, y),
              board,
              countNearbyEnvs(Rock),
              getFieldType,
            );
          switch (neighbours) {
          | _ when neighbours < 2 => Sand
          | _ when neighbours < 4 => field
          | _ => Rock
          };
        },
        row,
      ),
    board,
  );

let combineSpice = board =>
  Array.mapi(
    (x, row) =>
      Array.mapi(
        (y, field) =>
          switch (field) {
          | Spice =>
            let neighbours =
              countNeighbours(
                (x, y),
                board,
                countNearbyEnvs(Spice),
                getFieldType,
              );
            switch (neighbours) {
            | 1 => Rock
            | _ => Spice
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
            | 3 => Spice
            | 4 => Spice
            | _ => Sand
            };
          | Rock =>
            let neighbours =
              countNeighbours(
                (x, y),
                board,
                countNearbyEnvs(Rock),
                getFieldType,
              );
            switch (neighbours) {
            | 3 => Spice
            | _ => Rock
            };
          | _ => Empty
          },
        row,
      ),
    board,
  );

let playingBoard =
  createSandBoard(~width=20, ~height=15)
  |> randomizeBoard(addRock, 3)
  |> combineRock
  |> randomizeBoard(addSpice, 3)
  |> combineSpice
  |> randomizeBoard(addHill, 6);

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