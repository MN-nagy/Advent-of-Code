import * as fs from "fs";

/*

Goal: Get biggest rectangle in the polygon

*/

type Edge = {
  minX: number;
  maxX: number;
  minY: number;
  maxY: number;
  isVertical: boolean;
};

type Point = {
  minX: number;
  maxX: number;
  minY: number;
  maxY: number;
};

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(INPUT, "utf-8").trim().split("\n");

const points: number[][] = content.map((i) => i.split(",").map(Number));

const edges: Edge[] = points.map((val, i, arr) => {
  let current = val;
  let next = arr[i + 1];
  if (i === arr.length - 1) {
    next = arr[0];
  }

  const minX = Math.min(current[0], next[0]);
  const maxX = Math.max(current[0], next[0]);
  const minY = Math.min(current[1], next[1]);
  const maxY = Math.max(current[1], next[1]);
  const isVertical = minX === maxX ? true : false;

  const edge: Edge = {
    minX,
    maxX,
    minY,
    maxY,
    isVertical,
  };

  return edge;
});

function collisionCheck(edge: Edge, candidate: Point) {
  let notColliding = true;
  if (edge.isVertical === true) {
    if (
      edge.minX > candidate.minX &&
      edge.minX < candidate.maxX &&
      edge.maxY > candidate.minY &&
      edge.minY < candidate.maxY
    )
      notColliding = false;
  } else {
    if (
      edge.minY > candidate.minY &&
      edge.minY < candidate.maxY &&
      edge.maxX > candidate.minX &&
      edge.minX < candidate.maxX
    )
      notColliding = false;
  }
  return notColliding;
}

function rayTracing(edge: Edge, candidate: Point): boolean {
  // linear Interpolation slope x = xi + ((py - yi) - (xj - xi)) / (yj - yi)
  // or Manhattan Logic "as all to-be-checked edges are vertical"
  const point = [
    (candidate.maxX + candidate.minX) / 2,
    (candidate.maxY + candidate.minY) / 2,
  ];

  return edge.minX > point[0] && edge.maxY > point[1] && edge.minY <= point[1];
}

let highestArea = 0;
for (let i = 0; i < points.length; i++) {
  let currentRec = points[i];
  for (let j = i + 1; j < points.length; j++) {
    let nextRec = points[j];

    const minX = Math.min(currentRec[0], nextRec[0]);
    const maxX = Math.max(currentRec[0], nextRec[0]);
    const minY = Math.min(currentRec[1], nextRec[1]);
    const maxY = Math.max(currentRec[1], nextRec[1]);

    const candidate = {
      minX,
      maxX,
      minY,
      maxY,
    };

    let hits = 0;
    let valid = true;
    for (const edge of edges) {
      if (collisionCheck(edge, candidate)) {
        if (edge.isVertical) {
          if (rayTracing(edge, candidate)) hits++;
        }
      } else {
        valid = false;
        break;
      }
    }
    if (!valid) continue;

    if (hits % 2 === 0) {
      continue;
    }

    const area =
      (Math.abs(candidate.maxX - candidate.minX) + 1) *
      (Math.abs(candidate.maxY - candidate.minY) + 1);

    highestArea = highestArea < area ? area : highestArea;
  }
}

console.log(highestArea);
