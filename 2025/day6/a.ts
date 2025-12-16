import * as fs from "fs";

/*

Goal: Get fresh ingrediants

*/

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(INPUT, "utf-8").trim();

let problems = content.split("\n");
let total = 0n;
let problemAssimbler: string[] = [];

for (let col = 0; col < problems[0].length; col++) {
  let end = problems.length;
  let AccumulatedNum = "";
  let char = "";

  // to check colomns
  for (let row = 0; row < end; row++) {
    char = problems[row][col];
    if (char === undefined) {
      char = " ";
    }
    AccumulatedNum += char;
    if (!problemAssimbler[row]) {
      problemAssimbler[row] = "";
    }

    problemAssimbler[row] += char;
  }

  if (AccumulatedNum.trim() === "" || col + 1 === problems[0].length) {
    total += BigInt(
      solveProblem(
        String(problemAssimbler.pop()).trim(),
        problemAssimbler.filter((str) => str.trim() !== "").map(Number),
      ),
    );
    problemAssimbler = [];
  }
}

function solveProblem(operator: string, number: number[]): number {
  switch (operator) {
    case "*":
      return number.reduce((a, b) => a * b);
    case "+":
      return number.reduce((a, b) => a + b);
    default:
      return 0;
  }
}

console.log(total);
