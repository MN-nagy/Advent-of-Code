import * as fs from "fs";

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content: string = fs.readFileSync(INPUT, "utf-8").trim();
const idRanges: string[] = content.split(",");

let total: number = 0;

for (let id of idRanges) {
  const [start, end] = id.split("-");

  for (let idNum: number = Number(start); idNum <= Number(end); idNum++) {
    const idString: string = String(idNum);
    if (idString.length % 2 == 0) {
      const halfIndex: number = idString.length / 2;
      const leftHandSide: string = idString.slice(0, halfIndex);
      const rightHandSide: string = idString.slice(halfIndex);
      if (leftHandSide === rightHandSide) total += idNum;
    }
  }
}

console.log(total);
