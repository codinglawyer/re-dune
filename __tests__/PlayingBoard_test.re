open Jest;
open Expect;
open PlayingBoard;
open SharedTypes;

describe("module Game", () => {
  describe("method createSandBoard", () =>
    test("will create 3x2 playing board", () =>
      createSandBoard((3, 2))
      |> expect
      |> toEqual([|[|Sand, Sand|], [|Sand, Sand|], [|Sand, Sand|]|])
    )
  );
  describe("method randomizeBoard", () => {
    test("will add Rocks to the board", () =>
      randomizeBoard(
        addRock,
        3,
        [|[|Sand, Sand|], [|Sand, Sand|], [|Sand, Sand|]|],
      )
      |> expect
      |> toEqual([|[|Rock, Rock|], [|Sand, Sand|], [|Sand, Sand|]|])
    );
    test("will add Spice to the board", () =>
      randomizeBoard(
        addSpice,
        3,
        [|[|Rock, Rock|], [|Sand, Sand|], [|Sand, Sand|]|],
      )
      |> expect
      |> toEqual([|[|Rock, Rock|], [|Spice, Sand|], [|Sand, Sand|]|])
    );
    test("will add Hills to the board", () =>
      randomizeBoard(
        addHill,
        6,
        [|[|Rock, Rock|], [|Spice, Sand|], [|Sand, Sand|]|],
      )
      |> expect
      |> toEqual([|[|Rock, Rock|], [|Spice, Sand|], [|Sand, Sand|]|])
    );
  });

  describe("method getFieldType", () => {
    test(
      "when field's coordinates refer to the field that doesn't exists since it's a neigbor of an edge field - return Empty type",
      () =>
      getFieldType(
        ((-1), 5),
        [|[|Rock, Rock|], [|Spice, Sand|], [|Sand, Sand|]|],
      )
      |> expect
      |> toEqual(Empty)
    );
    test(
      "when field's coordinates refer to the field - return that field's type",
      () =>
      getFieldType(
        (0, 0),
        [|[|Rock, Rock|], [|Spice, Sand|], [|Sand, Sand|]|],
      )
      |> expect
      |> toEqual(Rock)
    );
  });

  describe("method countNeighbours", () =>
    test(
      "count how many neighbouring fields belongs to the same type as the original field",
      () =>
      countNeighbours(
        (0, 0),
        getFieldType,
        [|[|Rock, Rock|], [|Spice, Sand|], [|Sand, Sand|]|],
        compute(Rock),
      )
      |> expect
      |> toEqual(1)
    )
  );
  describe("method combineRocks", () =>
    test("combines Rocks env fields on the board to bigger units", () =>
      combineRocks([|[|Rock, Rock|], [|Sand, Rock|], [|Rock, Rock|]|])
      |> expect
      |> toEqual([|[|Rock, Rock|], [|Rock, Rock|], [|Rock, Rock|]|])
    )
  );
  describe("method combineSpice", () =>
    test("combines Spice env fields on the board to bigger units", () =>
      combineSpice([|[|Sand, Sand|], [|Sand, Sand|], [|Sand, Sand|]|])
      |> expect
      |> toEqual([|[|Spice, Spice|], [|Sand, Sand|], [|Spice, Spice|]|])
    )
  );
  describe("method createPlayingBoard", () =>
    test("will create 3x2 playing board", () =>
      createPlayingBoard(~width=3, ~height=2)
      |> expect
      |> toEqual([|[|Sand, Spice|], [|Spice, Spice|], [|Sand, Spice|]|])
    )
  );
});