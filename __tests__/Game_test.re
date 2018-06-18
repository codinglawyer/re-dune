open Jest;
open Expect;
open Game;

describe("module Game", () =>
  describe("method createPlayingBoard", () =>
    test("will create 3x2 playing board", () =>
      createPlayingBoard(~height=3, ~width=2)
      |> expect
      |> toEqual([|
           [|Sand, Sand|],
           [|Sand, Sand|],
           [|Sand, Sand|],
         |])
    )
  )
);