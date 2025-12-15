import * as fs from "fs";

/*

Goal: get num paper rolls

*/

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(INPUT, "utf-8").trim();

const paperRollGrid: string[][] = content
  .split("\n")
  .map((raw) => raw.split(""));

const directions = [
  [-1, -1],
  [-1, 0],
  [-1, 1],
  [0, -1],
  [0, 1],
  [1, -1],
  [1, 0],
  [1, 1],
];

let total = 0;
let removedPaperRolls = 0;

do {
  let rollsToRemove: number[][] = [];
  removedPaperRolls = 0;
  for (let y = 0; y < paperRollGrid.length; y++) {
    for (let x = 0; x < paperRollGrid[y].length; x++) {
      if (paperRollGrid[y][x] === "@") {
        let paperRollCount = 0;
        for (const direction of directions) {
          const neighborY = y + direction[0];
          const neighborX = x + direction[1];

          if (isValidDirection(neighborY, neighborX, paperRollGrid[y].length)) {
            if (paperRollGrid[neighborY][neighborX] === "@") {
              paperRollCount += 1;
            }
          }
        }
        if (paperRollCount < 4) {
          total += 1;
          rollsToRemove.push([y, x]);
          removedPaperRolls += 1;
        }
      }
    }
  }

  for (const toBeRemoved of rollsToRemove) {
    paperRollGrid[toBeRemoved[0]][toBeRemoved[1]] = ".";
  }
} while (removedPaperRolls);

function isValidDirection(
  nY: number,
  nX: number,
  xLen: number,
  yLen: number = paperRollGrid.length,
): boolean {
  if (nY >= yLen || nY < 0) {
    return false;
  }

  if (nX >= xLen || nX < 0) {
    return false;
  }

  return true;
}

console.log(total);
