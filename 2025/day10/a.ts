import * as fs from "fs";

/*

Goal: get presses count

*/

type Matrix = {
  vector: number[];
  buttons: number[][];
};

const INPUT = "./input.txt";
const TEST_INPUT = "./testinput.txt";

const content = fs.readFileSync(INPUT, "utf-8").trim().split("\n");

// parsing into lights and buttons
const initMatrix: Matrix[] = content.map((val) => {
  const lightMatch = val.match(/\[(.*?)\]/);
  const target = lightMatch![1];

  const vector: number[] = target.split("").map((c) => (c === "#" ? 1 : 0));

  const buttonMatch = val.matchAll(/\(([\d,]+)\)/g);
  const buttons: number[][] = [];

  for (const match of buttonMatch) {
    const indices = match[1].split(",").map(Number);

    const buttonVector = new Array(vector.length).fill(0);

    for (const i of indices) {
      buttonVector[i] = 1;
    }

    buttons.push(buttonVector);
  }

  return { vector, buttons };
});

let minTotalPresses = 0;

function solve(target: number[], buttons: number[][]): number {
  const numRow = target.length; // Lights
  const numCol = buttons.length; // Buttons

  // transpose: light | button, button | [target]
  const matrix: number[][] = [];
  for (let r = 0; r < numRow; r++) {
    const row: number[] = [];
    for (let c = 0; c < numCol; c++) {
      row.push(buttons[c][r]);
    }
    row.push(target[r]);
    matrix.push(row);
  }

  const pivotCol: number[] = new Array(numRow).fill(-1);

  for (let row = 0, col = 0; row < numRow && col < numCol; row++, col++) {
    let pivotRow = row;
    while (pivotRow < numRow && matrix[pivotRow][col] === 0) {
      pivotRow++;
    }

    // if no pivot found, move start of staircase to the next col
    if (pivotRow === numRow) {
      row--;
      continue;
    }

    // found a pivote (swap)
    [matrix[row], matrix[pivotRow]] = [matrix[pivotRow], matrix[row]];
    pivotCol[row] = col; // needed for the XOR operation

    for (let r = 0; r < numRow; r++) {
      // if another row has 1 on the col remove it (only current row can own the col)
      if (r != row && matrix[r][col] === 1) {
        for (let c = col; c <= numCol; c++) {
          // XOR the current row with the owner row (Question: why are we doing it to all the col after the owned col as well ?)
          // this loop will case use to do matrix[r][c] ^ matrix[row][c] for all cols from current col to last col ??
          matrix[r][c] ^= matrix[row][c];
        }
      }
    }
  }

  // now we should have a clean stare case;

  // getting the pivot cols: (needed to know the free cols)
  const pCols = new Set(pivotCol.filter((c) => c !== -1));

  const freeCols: number[] = [];
  for (let c = 0; c < numCol; c++) {
    if (!pCols.has(c)) {
      freeCols.push(c);
    }
  }

  // won't implement the unsolvable gurd for now.

  // getting the smallest clicks possible

  let minPresses = Infinity;
  const numFree = freeCols.length;
  const combinatons = 1 << numFree; // trick to get 2^N (if theres 2 free then there's only 4 possible combinatons)

  // help me visualize what's happening here with an example
  // my understanding is that it gets the current row and calculates it's presses leading to target with each combination of the free cols,
  // then set the lowest one to minPresses;
  for (let i = 0; i < combinatons; i++) {
    const sol = new Array(numCol).fill(0);

    // getting combinatons
    for (let b = 0; b < numFree; b++) {
      // understanding: checking if (floor(i / 2^b) & 1) will resul in either 0000 or 0001
      // this is effectivly setting the free cols from 0 to 1 in the solution
      if ((i >> b) & 1) {
        sol[freeCols[b]] = 1;
      }
    }

    for (let r = numRow - 1; r >= 0; r--) {
      const pCol = pivotCol[r]; // the last step in the staircase

      // skip if it's a free col
      if (pCol === -1) continue;
      let val = matrix[r][numCol]; // the target
      // whould this be out of bounds sense we start with the final step ?
      // or do it don't matter as we have free cols that well be skiped ?
      for (let c = pCol + 1; c < numCol; c++) {
        // this loop seems to loop over only the free cols without the pivots
        if (matrix[r][c] === 1) {
          val ^= sol[c];
        }
      }
      sol[pCol] = val;
    }

    const row_presses = sol.reduce((sum, val) => sum + val, 0);
    minPresses = Math.min(minPresses, row_presses);
  }

  return minPresses;
}

for (const m of initMatrix) {
  const currPresses = solve(m.vector, m.buttons);

  minTotalPresses += currPresses;
}

console.log(minTotalPresses);
