# Bubble Sort in C

Bubble Sort is the simplest sorting algorithm, which works by repeatedly swapping adjacent elements if they are in the wrong order. This approach is not efficient for large datasets, as both its average and worst-case time complexity are high.

## How Bubble Sort Works

The array is sorted using multiple passes. After each pass, the largest unsorted element "bubbles up" to its correct position:

- **First pass**: The largest element moves to the end of the array.
- **Second pass**: The second largest element moves to the second-last position, and so on.

In each pass, we only process elements that haven’t already moved to their correct position. After `k` passes, the largest `k` elements will be in the last `k` positions.

### Detailed Process

1. **Compare and Swap**: In each pass, compare adjacent elements. If the current element is larger than the next one, swap them.
2. **Largest to Correct Position**: By the end of a pass, the largest unsorted element is at its correct position in the array.
3. **Repeat**: For each subsequent pass, the algorithm processes the remaining unsorted elements until the array is fully sorted.

This method is easy to understand but is inefficient for large datasets due to its time complexity of O(n²) in both the average and worst cases.

_Source: [GeeksforGeeks - Bubble Sort](https://www.geeksforgeeks.org/bubble-sort-algorithm/)_
