class Graph {
  graph: string[];
  private memo: Map<string, number>;

  constructor(graph: string[]) {
    this.graph = graph;
    this.memo = new Map();
  }

  getNeigbors(r: number, c: number): string[] {
    const char = this.graph[r][c];
    const nextRow = r + 1;

    if (nextRow >= this.graph.length) return [];

    if (char === "." || char === "S") {
      return [`${nextRow},${c}`];
    }

    if (char === "^") {
      const niegbors = [];
      if (c - 1 >= 0) niegbors.push(`${r},${c - 1}`);
      if (c + 1 < this.graph[0].length) niegbors.push(`${r},${c + 1}`);
      return niegbors;
    }

    return [];
  }

  invalidDirection(r: number, c: number): boolean {
    if (r < 0 || r >= this.graph.length || c < 0 || c >= this.graph[0].length)
      return true;
    return false;
  }

  ModedBFS(): number {
    let splitcount = 0;
    const queue: string[] = [`0,${this.graph[0].indexOf("S")}`];
    const visited = new Set<string>();
    visited.add(`0,${this.graph[0].indexOf("S")}`);

    while (queue.length > 0) {
      const currentVertex = queue.shift()!;
      const [r, c] = currentVertex.split(",").map(Number);

      if (this.graph[r][c] === "^") {
        splitcount += 1;
      }

      const niegbors = this.getNeigbors(r, c);

      for (const niegbor of niegbors) {
        if (!visited.has(niegbor)) {
          visited.add(niegbor);
          queue.push(niegbor);
        }
      }
    }

    return splitcount;
  }

  dpDFS(r: number, c: number): number {
    if (r >= this.graph.length) {
      return 1;
    }

    if (this.invalidDirection(r, c)) {
      return 0;
    }

    const currentVertexKey = `${r},${c}`;

    if (this.memo.has(currentVertexKey)) {
      return this.memo.get(currentVertexKey)!;
    }

    const currentVertex = this.graph[r][c];

    let count = 0;
    if (currentVertex === "." || currentVertex === "S") {
      count += this.dpDFS(r + 1, c);
    } else {
      const rightTimelines = this.dpDFS(r + 1, c + 1);
      const leftTimelines = this.dpDFS(r + 1, c - 1);

      count += rightTimelines + leftTimelines;
    }

    this.memo.set(currentVertexKey, count);
    return count;
  }
}

export { Graph };
