import * as fs from "fs";

const REAL = "./day1.txt";
// const TEST = "./test.txt";

let content: string;
try {
  content = fs.readFileSync(REAL, "utf-8").trim();
} catch (err) {
  throw new Error(`Falid to parse the file: ${(err as Error).message}`);
}

let left: number[] = [];
let right: number[] = [];

for (let line of content.split("\n")) {
  let [l, r] = line.trim().split(/\s+/);
  left.push(Number(l));
  right.push(Number(r));
}

let freqArr: number[] = new Array(100000).fill(0);

for (let n of right) {
  freqArr[n] += 1;
}

let total = 0;
for (let n of left) {
  total += n * freqArr[n];
}

console.log(total);
