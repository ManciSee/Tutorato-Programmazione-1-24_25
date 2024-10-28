#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;  
    static unsigned int m_z = 789123;  

    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);

    return (m_z << 16) + m_w;  
}

struct parametri{
    int N;
    char w;
};

struct node {
    char data[20];
    struct node *next;
};

typedef struct node Node;

void insertHead(Node **head, char *string){
    if(*head == NULL){
        *head = malloc(sizeof(Node));
        strcpy((*head)->data, string);
        (*head)->next = NULL;
    }
    else {
        Node *new = malloc(sizeof(Node));
        strcpy(new->data, string);
        new->next = *head;
        *head = new;
    }
}

void insertString(Node **head, char *string){
    if(*head == NULL){
        insertHead(head, string);
        return;
    }

    Node *ptr = *head;
    Node *prev = NULL;

    while (ptr && strcmp(ptr->data, string) < 0){       // ordine lessicografico con < 0 => {'stringa1' < 'stringa2'}
        prev = ptr;
        ptr = ptr->next;
    }

    if(prev == NULL){
        insertHead(head, string);
        return;
    }

    Node *new = malloc(sizeof(Node));
    strcpy(new->data, string);
    prev->next = new;
    new->next = ptr;
}

void printList(Node *head){
    Node *tmp = head;

    while(tmp){
        printf("%s\n", tmp->data);
        tmp = tmp->next;
    }
}

struct parametri readInput(char *argv[], int argc){
    if(argc != 3){
        fprintf(stderr, "Il numero di argomenti deve essere '3'\n");
        exit(-1);
    }

    char **end = malloc(sizeof(char*));
    int N = (int) strtod(argv[1],end);

    if(N < 10 || N > 20){ 
        fprintf(stderr, "Il numero N deve essere compreso tra 10 e 20\n");
        exit(-1);
    }

    if(strlen(argv[2]) != 1){
        fprintf(stderr, "Il terzo parametro deve essere un carattere singolo\n");
        exit(-1);
    }

    struct parametri p = {N, argv[2][0]};
    return p;
}

char* genString(int len, const char range[2]){ // range[2] = {'a','z'}
    char *s = calloc(len, sizeof(char));

    for(int i=0; i<len; i++){
        s[i] = get_random() % (range[1]-range[0]+1)+range[0];
    }
    return s;
}

Node** genList(int N){
    Node **head = malloc(sizeof(Node*));
    *head = NULL;

    char range[2] = {'a','z'};
    char *tmp = NULL;

    for(int i=0; i<N; i++){
        int L = get_random() % (15-5 +1)+5;
        tmp = genString(L, range);
        insertString(head, tmp);

        free(tmp);
    }
    return head;
}

void printOcc(Node *head, char w){
    Node *tmp = head;
    int count = 0;

    while(tmp){
        char* s = tmp->data;

        for(int i=0; i<strlen(s); i++){
            if(s[i] == w)
                count++;
        }
        tmp = tmp->next;
    }

    printf("Il numero di occorrenze di %c: %d\n",w, count);
}

int main(int argc, char*argv[]){
    struct parametri p = readInput(argv,argc);
    Node **head = genList(p.N);
    printList(*head);
    printOcc(*head, p.w);
}