[%bs.raw {|require('./playingBoard.css')|}];
open SharedTypes;

type playingBoard = array(array(env));

let addRock = (num: int, field: env) =>
  switch (num) {
  | 1 => Rock
  | _ => field
  };

let addSpice = (num: int, field: env) =>
  switch (field) {
  | Sand =>
    switch (num) {
    | 1 => Spice
    | _ => field
    }
  | _ => field
  };

let addHill = (num: int, field: env) =>
  switch (field) {
  | Rock =>
    switch (num) {
    | 1 => Hill
    | _ => field
    }
  | _ => field
  };

let createSandBoard = ((width: int, height: int)) =>
  Array.make_matrix(width, height, Sand);

let randomizeBoard = (fn: (int, env) => env, seed: int, board: playingBoard) =>
  Array.map(
    row => Array.map(field => fn(Random.int(seed), field), row),
    board,
  );

let getFieldType = ((y: int, x: int), board: playingBoard) =>
  switch (y, x) {
  | _ when y < 0 || y >= Array.length(board) => Empty
  | _ when x < 0 || x >= Array.length(board[0]) => Empty
  | _ => board[y][x]
  };

let compute = (env: env, sum: int, field: env) =>
  env === field ? sum + 1 : sum;

let countNeighbours =
    (
      (x, y),
      getFieldFn: ((int, int), playingBoard) => env,
      board,
      countFn: (int, env) => int,
    ) =>
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

let combineRocks = (board: playingBoard) =>
  Array.mapi(
    (x, row) =>
      Array.mapi(
        (y, field) => {
          let neighbours =
            countNeighbours((x, y), getFieldType, board, compute(Rock));
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

let combineSpice = (board: playingBoard) =>
  Array.mapi(
    (x, row) =>
      Array.mapi(
        (y, field) => {
          let curriedCountNeighbours =
            countNeighbours((x, y), getFieldType, board);
          switch (field) {
          | Spice =>
            let neighbours = curriedCountNeighbours(compute(Spice));
            switch (neighbours) {
            | 1 => Rock
            | _ => Spice
            };
          | Sand =>
            let neighbours = curriedCountNeighbours(compute(Sand));
            switch (neighbours) {
            | 3 => Spice
            | 4 => Spice
            | _ => Sand
            };
          | Rock =>
            let neighbours = curriedCountNeighbours(compute(Rock));
            switch (neighbours) {
            | 3 => Spice
            | _ => Rock
            };
          | _ => Empty
          };
        },
        row,
      ),
    board,
  );

let createPlayingBoard = (~width: int, ~height: int) =>
  (width, height)
  |> createSandBoard
  |> randomizeBoard(addRock, 3)
  |> combineRocks
  |> randomizeBoard(addSpice, 3)
  |> combineSpice
  |> randomizeBoard(addHill, 6);

let playingBoard = createPlayingBoard(~width=20, ~height=15);

let component = ReasonReact.statelessComponent("Game");
let make = _children => {
  ...component,
  render: _self =>
    <div>
      <div className="game">
        (
          playingBoard
          |> Array.mapi((i, row) => <Field key=(string_of_int(i)) row />)
          |> ReasonReact.array
        )
      </div>
    </div>,
};