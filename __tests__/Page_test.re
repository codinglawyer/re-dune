open Jest;
open Expect;
open Game;

describe("re-dune", () =>
  test("create playing board of 2", () =>
    createPlayingBoard(2, 3)
    |> expect
    |> toEqual([|
         [|"field", "field"|],
         [|"field", "field"|],
         [|"field", "field"|],
       |])
  )
);
