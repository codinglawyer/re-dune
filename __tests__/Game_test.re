open Jest;
open Expect;
open Game;

describe("module Game", () => {
  describe("method createSandBoard", () =>
    test("will create 3x2 playing board", () =>
      createSandBoard(~height=2, ~width=3)
      |> expect
      |> toEqual([|[|Sand, Sand|], [|Sand, Sand|], [|Sand, Sand|]|])
    )
  );
  describe("method randomizeBoard", () =>
    test("will add Rocks to the board", () =>
      randomizeBoard(addRock, 3, [|[|Sand, Sand|], [|Sand, Sand|], [|Sand, Sand|]|])
      |> expect
      |> toEqual([|[|Rock, Rock|], [|Sand, Sand|], [|Sand, Sand|]|])
    )
  );
  describe("method randomizeBoard", () =>
    test("will add Spice to the board", () =>
      randomizeBoard(addSpice, 3, [|[|Rock, Rock|], [|Sand, Sand|], [|Sand, Sand|]|])
      |> expect
      |> toEqual([|[|Rock, Rock|], [|Spice, Sand|], [|Sand, Sand|]|])
    )
  );
  describe("method randomizeBoard", () =>
    test("will add Hills to the board", () =>
      randomizeBoard(addHill, 6, [|[|Rock, Rock|], [|Spice, Sand|], [|Sand, Sand|]|])
      |> expect
      |> toEqual([|[|Rock, Rock|], [|Spice, Sand|], [|Sand, Sand|]|])
    )
  );
});
