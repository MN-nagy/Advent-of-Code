import * as fs from "fs";
import { Graph } from "./Graph";

/*

Goal: Get split count

*/

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(INPUT, "utf-8").trim();
const graph = new Graph(content.split("\n"));

console.log(graph.ModedBFS());
