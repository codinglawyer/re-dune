open Jest;
open Expect;
open Structures;

describe("module Structures", () => {
  describe("buildTick", () => {
    test("increase structure build progress by one", () => {
      let testStructure = { ...smallConcreteSlab, buildProgress: 0 };
      let nextStructure = buildTick(testStructure);
      expect(nextStructure.buildProgress) |> toEqual(1);
    });
  });
});
