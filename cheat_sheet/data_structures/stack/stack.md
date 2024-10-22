# Stack in C

A stack is a linear data structure that stores a collection of items of the same type.

In a stack, the insertion and removal of elements occur at a single endpoint. The stack operates on the **Last In, First Out (LIFO)** principle. When an element is "pushed" onto the stack, it becomes the first item that will be "popped" off. To access the earliest inserted item, you must first pop all the items placed on top.

## Common Uses of Stacks

Stacks are used to solve several well-known problems, such as:

- Tower of Hanoi
- N-Queens Problem
- Infix to Prefix Conversion

In this article, we'll explore the concept of stack data structures and how to implement them using arrays in C.

## Stack Operations

The following are the basic operations that can be performed on a stack:

- **push**: Adds an element to the top of the stack.
- **pop**: Removes the topmost element from the stack.
- **isEmpty**: Checks if the stack is empty.
- **isFull**: Checks if the stack is full.
- **top**: Returns the topmost element of the stack without removing it.

_Source: [DigitalOcean - Stack in C](https://www.digitalocean.com/community/tutorials/stack-in-c)_
