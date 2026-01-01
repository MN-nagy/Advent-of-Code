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

left.sort((a, b) => a - b);
right.sort((a, b) => a - b);

let total: number = 0;
for (let i = 0; i < left.length; i++) {
  total += Math.abs(left[i] - right[i]);
}

console.log(total);
