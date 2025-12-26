import * as fs from "fs";

/*

Goal: Get biggest rectangle

*/

interface Edge {
  minX: number;
  maxX: number;
  minY: number;
  maxY: number;
  isVertical: boolean;
}

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(INPUT, "utf-8").trim().split("\n");

const grid: Array<Array<number>> = [];

let largestArea = 0;
let edges: Array<Edge> = [];

for (const coordinate of content) {
  grid.push(coordinate.split(",").map(Number));
}

for (let i = 0; i < grid.length; i++) {
  const point1 = grid[i];
  const point2 = grid[(i + 1) % grid.length];

  edges.push({
    minX: Math.min(point1[0], point2[0]),
    maxX: Math.max(point1[0], point2[0]),
    minY: Math.min(point1[1], point2[1]),
    maxY: Math.max(point1[1], point2[1]),
    isVertical: point1[0] === point2[0],
  });
}

for (let i = 0; i < grid.length; i++) {
  const cornerOne = grid[i];
  for (let j = i + 1; j < grid.length; j++) {
    const cornerTwo = grid[j];
    let isValid = true;

    // Define candidate with correct min/max immediately
    const currentCandidate = {
      minX: Math.min(cornerOne[0], cornerTwo[0]),
      maxX: Math.max(cornerOne[0], cornerTwo[0]),
      minY: Math.min(cornerOne[1], cornerTwo[1]),
      maxY: Math.max(cornerOne[1], cornerTwo[1]),
    };

    // 1. Slicing Check
    for (let edge of edges) {
      if (edge.isVertical) {
        if (
          edge.minX > currentCandidate.minX &&
          edge.minX < currentCandidate.maxX &&
          edge.maxY > currentCandidate.minY &&
          edge.minY < currentCandidate.maxY
        ) {
          isValid = false;
          break;
        }
      } else {
        if (
          edge.minY > currentCandidate.minY &&
          edge.minY < currentCandidate.maxY &&
          edge.maxX > currentCandidate.minX && // Fixed X check
          edge.minX < currentCandidate.maxX // Fixed X check
        ) {
          isValid = false;
          break;
        }
      }
    }

    if (!isValid) continue; // Optimization: Skip ray casting if sliced

    // 2. Ray Casting Check
    const midX = (currentCandidate.minX + currentCandidate.maxX) / 2;
    const midY = (currentCandidate.minY + currentCandidate.maxY) / 2;

    let hits = 0;
    for (const edge of edges) {
      if (edge.isVertical) {
        // Strict inequality on maxY to avoid double-counting vertices
        if (edge.minX > midX && edge.minY <= midY && edge.maxY > midY) {
          hits++;
        }
      }
    }

    if (hits % 2 === 0) {
      isValid = false;
    }

    // 3. Area Calculation
    if (isValid) {
      // Fix: Math.abs first, THEN add 1
      const width = Math.abs(cornerOne[0] - cornerTwo[0]) + 1;
      const height = Math.abs(cornerOne[1] - cornerTwo[1]) + 1;
      const currentArea = width * height;

      if (currentArea > largestArea) largestArea = currentArea;
    }
  }
}

console.log(largestArea);
