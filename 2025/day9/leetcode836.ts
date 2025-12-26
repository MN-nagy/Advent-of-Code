function maxArea(height: number[]): number {
  let left = 0;
  let right = height.length - 1;
  let maxCapacity = 0;

  while (left != right) {
    const currentCapacity =
      (right - left) * Math.min(height[left], height[right]);

    if (currentCapacity > maxCapacity) {
      maxCapacity = currentCapacity;
    }

    if (height[left] < height[right]) {
      left++;
    } else {
      right--;
    }
  }

  return maxCapacity;
}
