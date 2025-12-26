import * as fs from "fs";

/*

Goal: Get biggest rectangle

*/

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(INPUT, "utf-8").trim().split("\n");

const grid: Array<Array<number>> = [];

let largestArea = 0;

for (const coordinate of content) {
  grid.push(coordinate.split(",").map(Number));
}

for (let i = 0; i < grid.length; i++) {
  const cornerOne = grid[i];
  for (let j = i + 1; j < grid.length; j++) {
    const cornerTwo = grid[j];

    const currentArea =
      (cornerOne[0] - cornerTwo[0] + 1) * (cornerOne[1] - cornerTwo[1] + 1);

    if (currentArea > largestArea) largestArea = currentArea;
  }
}

console.log(largestArea);
