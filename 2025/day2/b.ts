import * as fs from "fs";

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(INPUT, "utf-8").trim();
const idRanges: string[] = content.split(",");

let total = new Set<number>();
let memoFactor = new Map<number, number[]>(); // to memoize length factors

for (let id of idRanges) {
  const [start, end] = id.split("-");

  for (let idNum = Number(start); idNum <= Number(end); idNum++) {
    const idString = String(idNum);
    const stringLen = idString.length;

    if (stringLen <= 1) continue; // to sckip single digit ids

    if (!memoFactor.has(stringLen)) {
      memoFactor.set(stringLen, getFactors(stringLen));
    }

    const factors: number[] = memoFactor.get(stringLen) ?? [];

    for (const count of factors) {
      const chunkSize: number = stringLen / count;
      const chunk = idString.slice(0, chunkSize);

      if (chunk.repeat(count) === idString) {
        total.add(idNum);
        break;
      }
    }
  }
}

function getFactors(num: number): number[] {
  let factors: number[] = [num];

  for (let i = 2; i <= Math.sqrt(num); i++) {
    if (num % i === 0) {
      factors.push(i);

      if (i !== num / i) {
        factors.push(num / i);
      }
    }
  }

  return factors;
}

let sum: number = 0;
for (const num of total) {
  sum += num;
}

console.log(sum);
