open Jest;
open Expect;
open Structures;

describe("module Structures", () => {
  describe("buildTick", () =>
    test("increase structure build progress by one", () => {
      let testStructure = {...smallConcreteSlab, buildProgress: 0};
      let nextStructure = buildTick(testStructure);
      expect(nextStructure.buildProgress) |> toEqual(1);
    })
  );

  describe("buildCompleteTick", () => {
    test("marks finished building as complete", () => {
      let testStructure = {
        ...smallConcreteSlab,
        buildProgress: smallConcreteSlab.buildTime,
      };
      let nextStructure = buildCompleteTick(testStructure);
      expect(nextStructure.buildComplete) |> toEqual(true);
    });

    test("didn't mark unfinished building as complete", () => {
      let testStructure = {
        ...smallConcreteSlab,
        buildProgress: smallConcreteSlab.buildTime - 1,
      };
      let nextStructure = buildCompleteTick(testStructure);
      expect(nextStructure.buildComplete) |> toEqual(false);
    });
  });
});
