#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  
    // Any data type can be stored in this node
    void  *data;
    struct Node *next;
};

// Function to insert data at head. This functions requires
// the size of the data type as extra argument
struct Node* insertAtHead(struct Node* head, void *data,
                   size_t data_size) {
  
    // Allocate memory for node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = malloc(data_size);
    newNode->next = head;

    // Copy contents of data to newly allocated memory.
    memcpy(newNode->data, data, data_size);

    return newNode;
}

// Function that access and prints the linked list. This function needs
// to know how many bytes of memory is to be read to print the data
// So a function pointer is required for printing different data type
void printList(struct Node *head, void (*fptr)(void *)) {
    while (head != NULL) {
        (*fptr)(head->data);
        head = head->next;
    }
}

// Helper function to print an integer
void printInt(void *n) {
   printf(" %d", *(int *)n);
}

// Helper function to print a float
void printFloat(void *f) {
   printf(" %f", *(float *)f);
}

int main() {

    // Create an int linked list
      // 10 -> 20 -> 30 -> 40
      struct Node *head = NULL;
     unsigned i_size = sizeof(int);
     int i_arr[4] = {40, 30, 20, 10};
      head = insertAtHead(head, i_arr, i_size);
      head = insertAtHead(head, i_arr + 1, i_size);
      head = insertAtHead(head, i_arr + 2, i_size);
      head = insertAtHead(head, i_arr + 3, i_size);
    
  
      // Printing the Integer list
    printf("Created integer linked list is \n");
    printList(head, printInt);
    
    // Create an float linked list
      // 10.1 -> 20.2 -> 30.3 -> 40.4
      head = NULL;
     unsigned f_size = sizeof(float);
     float f_arr[4] = {40.4, 30.3, 20.2, 10.1};
      head = insertAtHead(head, f_arr, f_size);
      head = insertAtHead(head, f_arr + 1, f_size);
      head = insertAtHead(head, f_arr + 2, f_size);
      head = insertAtHead(head, f_arr + 3, f_size);
    
  
      // Printing the Float list
    printf("\n\nCreated float linked list is \n");
    printList(head, printFloat);

    

    return 0;
}
