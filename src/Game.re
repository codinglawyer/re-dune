type env =
  | Sand
  | Ore
  | HighOre
  | Rocks
  | Mountains
  | Empty;

type playingBoard = array(array(env));

let addRocksSand = (num: int) =>
  switch (num) {
  | 1 => Rocks
  | _ => Sand
  };



let createBoard = (~width: int, ~height: int) =>
  Array.make_matrix(width, height, Sand);

let randomizeBoard = (board: playingBoard) =>
  Array.mapi(
    (x, row) => Array.mapi((y, _field) => addRocksSand(Random.int(3)), row),
    board,
  );

let playingBoard = createBoard(~width=20, ~height=15) |> randomizeBoard;


let getField = ((y: int, x: int), board: playingBoard) =>
  switch (y, x) {
  | _ when y < 0 || y >= Array.length(board) => Sand
  | _ when x < 0 || x >= Array.length(board[0]) => Sand
  | _ => board[y][x]
  };

let gett = ((x, y), board, field) =>
  List.fold_left(
    (sum, (diffX, diffY)) => {
      let neighbourY = y + diffY;
      let neighbourX = x + diffX;
      let field = getField((neighbourX, neighbourY), board);
      switch (field){
      | Sand => sum
      | Rocks => sum + 1
      };
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

   let someBoard =
   Array.mapi(
     (x, row) => Array.mapi((y, field) => {
       let neighbours = gett((x,y), playingBoard, field);
       switch(neighbours){
       | _ when neighbours < 2 => Sand
       | _ when neighbours < 4 => field
       | _ => Rocks
       }
      }, row),
     playingBoard,
   );


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
               someBoard,
            ),
          )
        )
      </div>
    </div>,
};