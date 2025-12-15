import * as fs from "fs";

/*

Goal: get biggest two digits with the preservasion of both batteries positions and the two digit position

*/

type Battery = {
  index: number;
  joltage: number;
};

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(TEST_INPUT, "utf-8").trim();

const banks = content.split("\n");
let total = 0;

for (const bank of banks) {
  let battery1: Battery = { index: 0, joltage: 0 };
  let battery2: Battery = { index: 0, joltage: 0 };
  let stash = 0;
  for (let i = 0; i < bank.length; i++) {
    let currentJoltage = Number(bank[i]);

    if (currentJoltage > battery2.joltage && i !== battery1.index) {
      battery2.joltage = currentJoltage;
    }

    if (battery2.joltage > battery1.joltage) {
      stash = Number(`${battery1.joltage}${battery2.joltage}`);
      battery1.index = i;
      battery1.joltage = currentJoltage;
      battery2.joltage = 0;
    }

    if (currentJoltage > battery1.joltage) {
      battery1.index = i;
      battery1.joltage = currentJoltage;
    }
  }

  if (battery2.joltage === 0) {
    total += stash;
  } else {
    total += Number(`${battery1.joltage}${battery2.joltage}`);
  }
}

console.log(total);
