// the ranges are guranted to be unsorted so no worst case gurds like midean-of-three needed
export function quickSort(nums: number[][], low: number, high: number): void {
  if (low < high) {
    let middle = partition(nums, low, high);
    quickSort(nums, low, middle - 1);
    quickSort(nums, middle + 1, high);
  }
}

function partition(nums: number[][], low: number, high: number): number {
  let pivot = high;
  let i = low - 1;
  for (let j = low; j < high; j++) {
    if (nums[j][0] < nums[pivot][0]) {
      i += 1;
      [nums[i], nums[j]] = [nums[j], nums[i]];
    }
  }

  [nums[i + 1], nums[pivot]] = [nums[pivot], nums[i + 1]];
  return i + 1;
}

for (let i = 0; i < grid.length; i++) {
  const cornerOne = grid[i];
  for (let j = i + 1; j < grid.length; j++) {
    const cornerTwo = grid[j];
    let isValid = true;
    const currentCandidate: Edge = {
      minX: Math.min(cornerOne[0], cornerTwo[0]),
      maxX: Math.max(cornerOne[0], cornerTwo[0]),
      minY: Math.min(cornerOne[1], cornerTwo[1]),
      maxY: Math.max(cornerOne[1], cornerTwo[1]),
      isVertical: cornerOne[0] === cornerTwo[0],
    };

    for (let edge of edges) {
      if (edge.isVertical) {
        if (
          edge.minX > currentCandidate.minX &&
          edge.minX < currentCandidate.maxX &&
          edge.maxY > currentCandidate.minY &&
          edge.minY < currentCandidate.maxY
        ) {
          isValid = false;
          break;
        }
      } else {
        if (
          edge.minY > currentCandidate.minY &&
          edge.minY < currentCandidate.maxY &&
          edge.maxX < currentCandidate.minX &&
          edge.minX > currentCandidate.minX
        ) {
          isValid = false;
          break;
        }
      }
    }

    const midX = (currentCandidate.minX + currentCandidate.maxX) / 2;
    const midY = (currentCandidate.minY + currentCandidate.maxY) / 2;

    let hits = 0;
    for (const edge of edges) {
      if (edge.isVertical) {
        if (edge.minX > midX && edge.minY <= midY && edge.maxY >= midY) {
          hits++;
        }
      }
    }

    if (hits % 2 === 0) {
      isValid = false;
    }

    if (isValid) {
      const currentArea =
        (Math.abs(cornerOne[0] - cornerTwo[0]) + 1) *
        (Math.abs(cornerOne[1] - cornerTwo[1]) + 1);

      if (currentArea > largestArea) largestArea = currentArea;
    }
  }
}
