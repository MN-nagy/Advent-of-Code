/*
problem order:

(x, y)

coordinates:
- outer box: (0,0)→(10,0)→(10,10)→(0,10)
- inner hole: (3,3)→(7,3)→(7,7)→(3,7)
*/

type Point = {
  x: number;
  y: number;
};

const outerBox: Point[] = [
  { x: 0, y: 0 },
  { x: 10, y: 0 },
  { x: 10, y: 10 },
  { x: 0, y: 10 },
];

const innerHole: Point[] = [
  { x: 3, y: 3 },
  { x: 7, y: 3 },
  { x: 7, y: 7 },
  { x: 3, y: 7 },
];

function isInsideDonut(p: Point): boolean {
  const out = isInsidePolygon(p, outerBox);
  const hole = isInsidePolygon(p, innerHole);

  return out && !hole;
}

function isInsidePolygon(p: Point, verices: Point[]): boolean {
  let j = verices.length - 1;
  let valid = 0;
  for (let i = 0; i < verices.length; i++) {
    const current = verices[i];
    const previous = verices[j];

    // y check
    if (current.y < p.y !== previous.y < p.y) {
      // x check
      const hitWall =
        previous.x +
        ((p.y - previous.y) * (current.x - previous.x)) /
          (current.y - previous.y);

      if (p.x < hitWall) {
        valid++;
      }
    }
    j = i;
  }

  return !(valid % 2 === 0);
}
