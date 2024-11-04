#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct data {
    char nome[255];
    char cognome[255];
    int eta;
    int peso;
    int altezza;
    char sesso;
};

typedef struct data Data;

struct node {
    Data data;
    struct node *next;
};

typedef struct node Node;

struct parameters {
    char input[255];
    char output[255];
};

typedef struct parameters Parameters;


// check if the string lenght is 4 and if the last characters match '.txt'
bool checkExt(char *s){
    return (strlen(s) >= 4) && (s[strlen(s)-1] == 't') && (s[strlen(s)-2] == 'x') && (s[strlen(s)-3] == 't') && (s[strlen(s)-4] == '.');
}


void printData(Data d){
    printf("%12s %12s %4d %4d %4d %4c\n", d.nome, d.cognome, d.eta, d.peso, d.altezza, d.sesso);
}

void printList(Node **head){
    Node *ptr = *head;

    while(ptr){
        printData(ptr->data);
        ptr = ptr->next;
    }
}

bool isEmpty(Node *head){
    return head == NULL;        // return 'true' or 'false'
}

// insert a new node at the head of the list
void insertHead(Node **head, Data d){
    Node *new = malloc(sizeof(Node));
    new->data = d;
    new->next = *head;
    *head = new;
}

// insert a new node after a given node in the list
void insertAfter(Node *node, Data d){
    Node *new = malloc(sizeof(Node));
    new->data = d;
    new->next = node->next;
    node->next = new;
}

// insert a node sorted by age
void insertOrdered(Node **head, Data d){

    // if the list is empty or the new data's age is less than the head node's age
    if(isEmpty(*head) || d.eta < (*head)->data.eta){
        insertHead(head, d);
        return;
    }

    Node *tmp = *head;
    Node *prev = NULL;

    while(tmp != NULL && tmp->data.eta < d.eta){
        prev = tmp;
        tmp = tmp->next;
    }

    // insert the new node after the previous node
    insertAfter(prev, d);
}

void delete(Node **head, Node *node){
    
    // if the node to be deleted is the head of the list
    if(*head == node){
        Node *tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }

    Node *tmp = *head;
    Node *prev = NULL;

    while(tmp->next && tmp != node){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp && tmp == node){
        prev->next = tmp->next;
        free(tmp);
    }
}

int lenghtList(Node **head){
    Node *tmp = *head;
    int count = 0;

    while(tmp){
        count++;
        tmp = tmp->next;
    }

    return count;
}

Parameters readInput(char *argv[], int argc){
    if(argc != 3){
        fprintf(stderr, "I paramatri devono essere '3'\n");
        exit(-1);
    }

    if(!checkExt(argv[1]) || !checkExt(argv[2])){
        fprintf(stderr,"I file devono essere '.txt'\n");
        exit(-1);
    }

    Parameters p;
    strcpy(p.input, argv[1]);
    strcpy(p.output, argv[2]);

    return p;
}

Node **readFile(char *fname){
    Node **head = malloc(sizeof(Node*));

    FILE *file = fopen(fname, "r");

    if(!file){
        fprintf(stderr, "Errore nell'apertura del file %s.\n", fname);
        exit(-1);
    }

    while(!feof(file)){
        Data d;
        fscanf(file, "%254s %254s %d %d %d %c", d.nome, d.cognome, &d.eta, &d.peso, &d.altezza, &d.sesso);

        if(!feof(file))
            insertOrdered(head, d);
    }
    fclose(file);

    return head;
}

float imc(Data d){
    // convert from 'cm' to 'm'
    float a = d.altezza / 100.0;
    return d.peso / (a*a);
}

Node *getMax(Node *head){
    Node *tmp = head;
    Node *max = head;

    while(tmp){
        if(tmp && imc(tmp->data) > imc(max->data))
            max = tmp;

        tmp = tmp->next;
    }   
    return max;
}

void writeFile(Node **head, char *fname){
    FILE *file = fopen(fname, "w");
    
    if(!file){
        fprintf(stderr, "Errore nell'apertura del file %s.", fname);
    }

    Node *tmp = *head;

    while(tmp){
        Data d = tmp->data;
        fprintf(file, "%s %s %d %d %d %c\n", d.nome, d.cognome, d.eta, d.peso, d.altezza, d.sesso);
        tmp = tmp->next;
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    // PUNTO A: Read the input parameters (input and output file names)
    Parameters p = readInput(argv, argc);

    printf("=======PUNTO A=======\n");
    printf("input = %s, output = %s\n", p.input, p.output);

    // PUNTO B: Read data from the input file and store it in a sorted linked list A
    Node **A = readFile(p.input);
    printf("\n=======PUNTO B=======\n");
    printList(A);  // Print the entire list A

    // PUNTO C: Find the person with the maximum IMC in list A
    Node *max = getMax(*A);
    printf("\n=======PUNTO C=======\n");
    printData(max->data);  // Print the data of the person with the maximum IMC

    // PUNTO D: Create a new list B with the 3 people with the highest IMC from list A
    printf("\n=======PUNTO D=======\n");
    Node** B = malloc(sizeof(Node*)); 
    for (int i = 0; i < 3; i++) {  
        Node *max = getMax(*A);  
        Data d = max->data;      
        delete(A, max);          
        insertHead(B, d);        
    }

    printf("A:\n");
    printList(A);
    printf("B:\n");
    printList(B);

    
    writeFile(B, p.output);
}