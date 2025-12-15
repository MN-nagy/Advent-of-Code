import * as fs from "fs";

/*

Goal: Get fresh ingrediants

*/

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(INPUT, "utf-8").trim();

let [r, i] = content.split("\n\n");
const ranges = r.split("\n");
const ingredients = i.split("\n");

let freshIngredientCount = 0;

for (const ingredient of ingredients) {
  for (const range of ranges) {
    const [start, end] = range.split("-");

    if (
      Number(start) <= Number(ingredient) &&
      Number(ingredient) <= Number(end)
    ) {
      freshIngredientCount += 1;
      break;
    }
  }
}

console.log(freshIngredientCount);
