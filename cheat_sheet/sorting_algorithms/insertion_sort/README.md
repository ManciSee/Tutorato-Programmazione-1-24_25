# Insertion Sort in C

Insertion Sort is a simple sorting algorithm that iteratively inserts each element of an unsorted list into its correct position within a sorted portion of the list. This process can be likened to sorting playing cards in your hands: you separate the cards into two groups—sorted and unsorted—and then take a card from the unsorted group and place it in the correct position among the sorted cards.

## How Insertion Sort Works

1. **Initialization**: Start with the second element of the array, as the first element is assumed to be sorted.
2. **Comparison and Insertion**:
   - Compare the second element with the first. If the second element is smaller, swap them.
   - Move to the third element, compare it with the first two elements, and place it in its correct position.
3. **Repeat**: Continue this process for each subsequent element until the entire array is sorted.

Insertion Sort is efficient for small datasets or partially sorted lists, with a time complexity of O(n²) in the average and worst cases. However, it performs well in practice on small arrays or lists that are already somewhat sorted.

_Source: [GeeksforGeeks - Insertion Sort](https://www.geeksforgeeks.org/bubble-sort-algorithm/)_
