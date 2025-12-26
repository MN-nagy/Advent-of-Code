import * as fs from "fs";

/*

Goal: Get Big Circutes

*/

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

interface Junction {
  id: number;
  x: number;
  y: number;
  z: number;
}

interface Edge {
  idOne: number;
  idTwo: number;
  distance: number;
}

// DSU Implementation
class UnionFind {
  private parent: number[];
  private size: number[];

  constructor(n: number) {
    this.parent = [];
    this.size = [];

    for (let i = 0; i < n; i++) {
      this.parent[i] = i;
      this.size[i] = 1;
    }
  }

  find(i: number): number {
    if (this.parent[i] === i) {
      return i;
    }

    this.parent[i] = this.find(this.parent[i])!;
    return this.parent[i];
  }

  union(i: number, j: number): boolean {
    const rootA = this.find(i)!;
    const rootB = this.find(j)!;

    if (rootA !== rootB) {
      this.parent[rootA] = rootB;
      this.size[rootB] += this.size[rootA];
      this.size[rootA] = 0;
      return true;
    }
    return false;
  }

  get sizes(): number[] {
    return this.size;
  }
}

const graph = fs.readFileSync(INPUT, "utf-8").trim().split("\n");
const junctions: Junction[] = [];
const edges: Edge[] = [];

// collecting junctions
for (let i = 0; i < graph.length; i++) {
  const [x, y, z] = graph[i].split(",").map(Number);
  const id = i;
  junctions.push({ id, x, y, z });
}

// collecting edges
for (let i = 0; i < junctions.length; i++) {
  const currentJunction = junctions[i];
  const idOne = currentJunction.id;
  for (let j = i + 1; j < junctions.length; j++) {
    const otherJunction = junctions[j];
    const idTwo = otherJunction.id;

    const dx = (otherJunction.x - currentJunction.x) ** 2;
    const dy = (otherJunction.y - currentJunction.y) ** 2;
    const dz = (otherJunction.z - currentJunction.z) ** 2;

    const distance = dx + dy + dz;

    edges.push({ idOne, idTwo, distance });
  }
}

// sorting ascending
edges.sort((a, b) => a.distance - b.distance);

// DSU
const dsu = new UnionFind(junctions.length);

let junctionNumber = junctions.length;

// return the
for (const edge of edges) {
  if (dsu.union(edge.idOne, edge.idTwo)) {
    junctionNumber -= 1;
    if (junctionNumber === 1) {
      console.log(junctions[edge.idOne].x * junctions[edge.idTwo].x);
      break;
    }
  }
}
