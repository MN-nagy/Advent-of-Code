import * as fs from "fs";

/*
  Goal: Get minimum presses count for Part 2
*/

type Matrix = {
  vector: number[];
  buttons: number[][];
};

const INPUT = "./input.txt";
const content = fs.readFileSync(INPUT, "utf-8").trim().split("\n");

// --- 1. Parsing ---
const initMatrix: Matrix[] = content
  .filter((line) => line.trim().length > 0)
  .map((val) => {
    const lightMatch = val.match(/\{(.*?)\}/);
    if (!lightMatch) throw new Error("Parse Error");
    const target = lightMatch[1].split(",").map(Number);

    const buttonMatch = val.matchAll(/\(([\d,]+)\)/g);
    const buttons: number[][] = [];

    for (const match of buttonMatch) {
      const indices = match[1].split(",").map(Number);
      const buttonVector = new Array(target.length).fill(0);
      for (const i of indices) buttonVector[i] = 1;
      buttons.push(buttonVector);
    }
    return { vector: target, buttons };
  });

let minTotalPresses = 0;

// --- 2. The Robust Solver ---
function solve(target: number[], buttons: number[][]): number {
  const numRow = target.length;
  const numCol = buttons.length;

  // Build Augmented Matrix
  const M: number[][] = [];
  for (let r = 0; r < numRow; r++) {
    const row: number[] = [];
    for (let c = 0; c < numCol; c++) row.push(buttons[c][r]);
    row.push(target[r]);
    M.push(row);
  }

  // A. Gaussian Elimination to RREF
  let pivotRow = 0;
  const colToPivotRow = new Map<number, number>();
  const freeCols: number[] = [];

  for (let c = 0; c < numCol; c++) {
    if (pivotRow >= numRow) {
      freeCols.push(c);
      continue;
    }

    let selection = pivotRow;
    while (selection < numRow && Math.abs(M[selection][c]) < 1e-6) {
      selection++;
    }

    if (selection === numRow) {
      freeCols.push(c);
      continue;
    }

    [M[pivotRow], M[selection]] = [M[selection], M[pivotRow]];

    const div = M[pivotRow][c];
    for (let j = c; j <= numCol; j++) M[pivotRow][j] /= div;

    for (let r = 0; r < numRow; r++) {
      if (r !== pivotRow) {
        const factor = M[r][c];
        if (Math.abs(factor) > 1e-9) {
          for (let j = c; j <= numCol; j++) M[r][j] -= factor * M[pivotRow][j];
        }
      }
    }

    colToPivotRow.set(c, pivotRow);
    pivotRow++;
  }

  // B. Consistency Check
  for (let r = pivotRow; r < numRow; r++) {
    if (Math.abs(M[r][numCol]) > 1e-4) return 0;
  }

  // C. Backtracking Search
  let globalMin = Infinity;

  // Dynamic Limit: The maximum presses can't reasonably exceed the largest target value
  // (Assuming min button effect is 1)
  const maxSearch = Math.max(...target) + 2;

  function backtrack(
    idx: number,
    currentPresses: number,
    currentFreeVals: Map<number, number>,
  ) {
    // Pruning: If just the free variables exceed our best total, stop.
    if (currentPresses >= globalMin) return;

    if (idx === freeCols.length) {
      let valid = true;
      let pivotPresses = 0;

      for (const [_, pRow] of colToPivotRow.entries()) {
        let val = M[pRow][numCol];

        for (const fCol of freeCols) {
          const coeff = M[pRow][fCol];
          const fVal = currentFreeVals.get(fCol)!;
          val -= coeff * fVal;
        }

        if (val < -1e-4) {
          valid = false;
          break;
        }
        const rounded = Math.round(val);
        if (Math.abs(val - rounded) > 1e-4) {
          valid = false;
          break;
        }

        pivotPresses += rounded;
      }

      if (valid) {
        globalMin = Math.min(globalMin, currentPresses + pivotPresses);
      }
      return;
    }

    const fCol = freeCols[idx];

    // FIX 1: Search up to maxSearch (handles targets like 302)
    for (let v = 0; v <= maxSearch; v++) {
      currentFreeVals.set(fCol, v);

      // FIX 2: Removed "currentPresses + v > globalMin" break.
      // Increasing 'v' might reduce pivot presses, lowering the total sum.
      backtrack(idx + 1, currentPresses + v, currentFreeVals);
    }
  }

  backtrack(0, 0, new Map());

  return globalMin === Infinity ? 0 : globalMin;
}

// --- 3. Main Loop ---
for (let i = 0; i < initMatrix.length; i++) {
  const m = initMatrix[i];
  const res = solve(m.vector, m.buttons);

  // Debug log for machines that still return 0 (should be none now)
  if (res === 0 && m.vector.some((x) => x !== 0)) {
    console.log(`Machine ${i} returned 0`);
  }

  minTotalPresses += res;
}

console.log(minTotalPresses);
