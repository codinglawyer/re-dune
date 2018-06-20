type structureKind =
  | ConstructionYard
  | SmallConcreteSlab
  | LargeConcreteSlab
  | Wall
  | Windtrap
  | Refinery
  | Outpost
  | Silo
  | Barracks
  | Wor
  | LightFactory
  | HeavyFactory
  | HiTechFactory
  | CannonTurret
  | RocketTurret
  | RepairFacility
  | HouseOfIX
  | Starport
  | Palace;

type coordinates = (int, int);

type layout = (int, int);

type structure = {
  kind: structureKind,
  coordinates,
  layout,
  buildCost: int,
  buildTime: int,
  buildComplete: bool,
  buildProgress: int,
  hitPoints: int,
  powerUsage: int,
};

/**
  Structures declaration
  ===============================================
  */

let smallConcreteSlab = {
  kind: SmallConcreteSlab,
  coordinates: (0, 0),
  layout: (1, 1),
  buildCost: 5,
  buildTime: 16,
  buildComplete: false,
  buildProgress: 0,
  hitPoints: 20,
  powerUsage: 0,
};

/**
  Structures modificators
  ===============================================
  */

let buildTick = structure => {
  ...structure,
  buildProgress: structure.buildProgress + 1,
};
