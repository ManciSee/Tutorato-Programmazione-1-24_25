# Queue in C

A queue in C is a linear data structure used to store and manage data elements. It follows the **First In, First Out (FIFO)** principle, meaning the first element added is the first to be removed.

In a queue, the element that enters the structure first will be the first one to be removed.

## Queue Structure

The queue operates based on the FIFO pattern, where the first element inserted is the first to be extracted.

### Key Concepts

- **Front and Rear pointers** are used to track the first and last elements in the queue.

### Initialization

- The queue is initialized by setting `Front = -1` and `Rear = -1`.

### Enqueue (Insertion)

- To insert an element, we first check if the queue is full (Overflow condition).
- If not, increment the `Rear` pointer by 1 and place the element at this new position.
- When inserting the first element, the `Front` pointer is set to 0.

### Dequeue (Removal)

- To remove an element, we first check if the queue is empty (Underflow condition).
- If the queue is not empty, the element at the `Front` pointer is removed, and the `Front` pointer is incremented by 1.
- If the last element is removed, both `Front` and `Rear` pointers are reset to -1.

This approach ensures efficient insertion and removal of elements while maintaining the order in which they were added.

_Source: [DigitalOcean - Queue in C](https://www.digitalocean.com/community/tutorials/queue-in-c)_
