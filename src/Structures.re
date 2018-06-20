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
  coordinates: coordinates,
  layout: layout,
  buildCost: int,
  buildTime: int,
  hitPoints: int,
  powerUsage: int,
};
