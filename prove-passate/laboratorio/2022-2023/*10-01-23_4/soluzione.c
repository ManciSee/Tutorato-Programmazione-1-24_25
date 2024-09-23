#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}


struct parametri {
    int N;
};

struct node {
    char data;
    struct node *next;
};

typedef struct node Node;

struct parametri readInput(char *argv[], int argc){
    if(argc != 2){
        fprintf(stderr, "Il numero di parametri è errato\n");
        exit(EXIT_FAILURE);
    }

    char **end = malloc(sizeof(char*));

    int x = (int) strtol(argv[1], end, 0);

    if(!*end || x<0){ // || = OR    && = AND
        fprintf(stderr, "'x' deve essere positivo\n");
        exit(-1);        
    }

    struct parametri p = {x};
    return p;
}

bool empty(Node *head){
    if(head == NULL)
        return true;
    return false;
    /*
        oppure :
            return head==NULL;
    */

}

void push(Node **head, char x){
    Node *new = malloc(sizeof(Node));

    new->data = x;
    new->next = *head;
    *head = new;
}

char pop(Node **head){
    if(empty(*head)){
        fprintf(stderr, "Lo stack è vuoto\n");
        exit(-1);          
    }

    char x = (*head)->data;
    Node* tmp = *head;
    (*head) = (*head)->next;

    free(tmp);
    return x;
}

char getRandomChar(char *s){
    return s[get_random() % strlen(s)];
}

char getVowel(){
    return getRandomChar("AEIOUaeiou");
}

char getConsonant(){
    return getRandomChar("QWRTYPDSFGHJKLZXCVBNMqwrtypdsfghjklzxcvbnm");
}

int char2int(char c) {
    char tmp[2];
    tmp[0] = c;
    tmp[1] = 0;
    char **end = malloc(sizeof(char*));
    int x = (int) strtol(tmp, end, 0);
    free(end);
    return x;
}

Node **fillStack(int N){
    Node **head = malloc(sizeof(Node*));
    *head = NULL;

    for(int j=0; j<N; j++){
        char x = getRandomChar("123456789");
        if(x>='1' && x<='4'){
            for(int i=0; i<char2int(x); i++){
                // for(int i=0; i<atoi(x); i++)
                push(head, getVowel());
            }
            push(head, x);
        } else {
            for(int i=0; i<char2int(x); i++){
                char c = getConsonant();
                if(c=='v')
                    c = '*';
                if(c=='w')
                    c = '?';
                push(head, c);
            }
            push(head, x);
        }
    }
    return head;
}

char **emptyStack(Node **head, int N){
    char **array = calloc(N, sizeof(char*));
    int idx = 0;

    while(!empty(*head)){       // finchè nello stack ci sono elementi
        char c = pop(head);
        int x = char2int(c);
        array[idx] = calloc(x, sizeof(char)+1);
        for(int j=0; j<x; j++){
            array[idx][j] = pop(head);
        }
        idx++;
    }
    return array;
}

void printArray(char **array, int N){
    for(int i=0; i<N; i++){
        printf("%s\n", array[i]);
    }
}


int main(int argc, char *argv[]){
    struct parametri p = readInput(argv, argc);
    Node **head = fillStack(p.N);

    char **array = emptyStack(head, p.N);
    printArray(array, p.N);
}

