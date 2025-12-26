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

  find(i: number) {
    if (this.parent[i] === i) {
      this.parent[i] = i;
      return i;
    }

    this.find(this.parent[i]);
  }

  union(i: number, j: number): boolean {
    const rootA = this.find(i)!;
    const rootB = this.find(j)!;

    if (rootA !== rootB) {
      this.parent[rootA] = rootB;
      this.size[rootB] += this.size[rootA];
      return true;
    }
    return false;
  }
}
