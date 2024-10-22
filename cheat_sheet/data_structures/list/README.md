# Generic Linked List in C

A generic linked list is a type of linked list that allows storing different types of data within a single linked list structure. This adds flexibility and reusability for various applications. Unlike languages like C++ and Java, C does not directly support generics, but we can implement generic behavior using a few techniques.

In this article, we will learn how to create a generic linked list in C, allowing the same linked list code to work with different data types.

## How to Create a Generic Linked List in C?

In C, we can use a **void pointer** and a **function pointer** to implement generic functionality.

### Key Concepts:

- **Void Pointers**: A void pointer can point to any data type. This allows us to use the same pointer to handle various types of data.
- **Pointer Size**: The size of all pointer types in C is the same, so we can easily allocate memory for a linked list node, regardless of the data type being stored.
- **Function Pointers**: A function pointer, along with the size of the data type, is used to process the actual content stored at the memory address pointed to by the void pointer.

By combining these techniques, we can create a flexible linked list structure that handles different types of data within the same framework.

_Source: [GeeksforGeeks - Generic Linked List in C](https://www.geeksforgeeks.org/generic-linked-list-in-c-2/)_
