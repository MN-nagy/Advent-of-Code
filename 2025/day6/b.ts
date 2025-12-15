import * as fs from "fs";
import { quickSort } from "./qicksort";

/*

Goal: Get fresh ingrediants

*/

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(INPUT, "utf-8").trim();

let [r, i] = content.split("\n\n");
let ranges = r.split("\n").map((range) => {
  let [s, e] = range.split("-");
  return [Number(s), Number(e)];
});

let freshIngredientCount = 0n;

/*
Could have also used "ranges.sort((a, b) => a[0] - b[0])",
but where's the fun in that!
*/
quickSort(ranges, 0, ranges.length - 1);

let mergedRanges: number[][] = [];
let rangeStart = ranges[0][0];
let rangeEnd = ranges[0][1];

for (let i = 0; i < ranges.length; i++) {
  if (ranges[i][0] <= rangeEnd) {
    rangeEnd = Math.max(rangeEnd, ranges[i][1]);
  } else {
    mergedRanges.push([rangeStart, rangeEnd]);
    rangeStart = ranges[i][0];
    rangeEnd = ranges[i][1];
  }
}

mergedRanges.push([rangeStart, rangeEnd]);

for (const range of mergedRanges) {
  freshIngredientCount += BigInt(range[1] - range[0] + 1);
}

console.log(freshIngredientCount);
