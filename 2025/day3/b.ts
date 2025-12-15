import * as fs from "fs";

/*

Goal: get biggest two digits with the preservasion of both batteries positions and the two digit position
B Goal: 12 batteries now -_-

*/

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(INPUT, "utf-8").trim();

const banks = content.split("\n");
let total = 0n;

for (const bank of banks) {
  let kohStack: number[] = [];
  let budget = bank.length - 12;
  for (const joltage of bank) {
    let currentJoltage = Number(joltage);

    while (currentJoltage > kohStack[kohStack.length - 1] && budget > 0) {
      kohStack.pop();
      budget -= 1;
    }
    kohStack.push(currentJoltage);
  }

  let finalInt = kohStack.slice(0, 12).join("");

  total += BigInt(finalInt);
}

console.log(total);
