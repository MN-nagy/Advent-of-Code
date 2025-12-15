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
