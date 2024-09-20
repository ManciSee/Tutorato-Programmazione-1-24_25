#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 51  // Definisce la lunghezza massima del nome del file

// Struttura del nodo per una lista collegata
typedef struct node {
    char data;  // Dato contenuto nel nodo (un carattere)
    struct node* next;  // Puntatore al nodo successivo
} Node;

// Struttura per memorizzare i parametri del programma
typedef struct {
    char in_filename[MAX_FILENAME_LENGTH];  // Nome del file di input
    char out_filename[MAX_FILENAME_LENGTH];  // Nome del file di output
    char c;  // Carattere di cui contare le occorrenze
} Parameters;

// Funzione per inserire un nodo all'inizio della lista
Node* insertHead(Node* head, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Alloca memoria per il nuovo nodo
    if (newNode == NULL) {  // Verifica se l'allocazione è fallita
        fprintf(stderr, "Errore: Allocazione di memoria fallita\n");
        exit(1);
    }
    newNode->data = data;  // Imposta il dato del nuovo nodo
    newNode->next = head;  // Collega il nuovo nodo all'inizio della lista
    return newNode;  // Restituisce il nuovo nodo come testa della lista
}

// Funzione per inserire un nodo alla fine della lista
Node* insertTail(Node* head, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Alloca memoria per il nuovo nodo
    if (newNode == NULL) {
        fprintf(stderr, "Errore: Allocazione di memoria fallita\n");
        exit(1);
    }
    newNode->data = data;  // Imposta il dato del nuovo nodo
    newNode->next = NULL;  // Il nuovo nodo sarà l'ultimo, quindi punta a NULL

    if (head == NULL) {  // Se la lista è vuota, il nuovo nodo è la testa
        return newNode;
    }

    // Trova l'ultimo nodo della lista
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;  // Aggiunge il nuovo nodo alla fine della lista
    return head;  // Restituisce la testa della lista
}

// Funzione per eliminare il primo nodo della lista
Node* deleteHead(Node* head) {
    if (head == NULL) {  // Se la lista è vuota, non fa nulla
        return NULL;
    }
    Node* newHead = head->next;  // Il nuovo nodo di testa sarà il successivo
    free(head);  // Libera la memoria del vecchio nodo di testa
    return newHead;  // Restituisce il nuovo nodo di testa
}

// Funzione per eliminare un nodo specifico dalla lista
Node* deleteNode(Node* head, Node* nodeToDelete) {
    if (head == NULL || nodeToDelete == NULL) {
        return head;  // Se la lista è vuota o il nodo è nullo, non fa nulla
    }

    if (head == nodeToDelete) {  // Se il nodo da eliminare è la testa, usa deleteHead
        return deleteHead(head);
    }

    // Cerca il nodo precedente a quello da eliminare
    Node* current = head;
    while (current->next != NULL && current->next != nodeToDelete) {
        current = current->next;
    }

    if (current->next == nodeToDelete) {
        current->next = nodeToDelete->next;  // Collega il nodo precedente al successivo
        free(nodeToDelete);  // Libera la memoria del nodo eliminato
    }

    return head;  // Restituisce la testa della lista
}

// Funzione per decodificare i parametri passati al programma
Parameters decodeParameters(int argc, char* argv[]) {
    Parameters params;
    if (argc != 4) {  // Verifica che ci siano esattamente 3 argomenti
        fprintf(stderr, "Errore: Numero errato di argomenti\n");
        exit(1);
    }

    // Copia i nomi dei file e il carattere c nei parametri
    strncpy(params.in_filename, argv[1], MAX_FILENAME_LENGTH - 1);
    params.in_filename[MAX_FILENAME_LENGTH - 1] = '\0';  // Assicura che la stringa sia terminata
    strncpy(params.out_filename, argv[2], MAX_FILENAME_LENGTH - 1);
    params.out_filename[MAX_FILENAME_LENGTH - 1] = '\0';
    params.c = argv[3][0];  // Il carattere è il primo della terza stringa

    return params;
}

// Funzione per leggere un file e creare una lista con i suoi caratteri
Node* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");  // Apre il file in lettura
    if (file == NULL) {
        fprintf(stderr, "Errore: Impossibile aprire il file %s\n", filename);
        exit(1);
    }

    Node* head = NULL;
    char c;
    while ((c = fgetc(file)) != EOF) {  // Legge ogni carattere fino alla fine del file
        if (c != '\n') {  // Ignora i caratteri di nuova riga
            head = insertTail(head, c);  // Inserisce il carattere alla fine della lista
        }
    }

    fclose(file);  // Chiude il file
    return head;  // Restituisce la lista
}

// Funzione per contare le occorrenze di un carattere nella lista
int countOccurrences(Node* head, char c) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {  // Scorre la lista
        if (current->data == c) {  // Se il carattere corrisponde, incrementa il contatore
            count++;
        }
        current = current->next;
    }
    return count;
}

// Funzione che elimina i nodi che hanno occorrenze maggiori o uguali a 'o'
Node* processL(Node* head, int o) {
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        int p = countOccurrences(head, current->data);  // Conta le occorrenze del carattere
        if (p >= o) {  // Se il numero di occorrenze è maggiore o uguale a 'o'
            Node* temp = current->next;
            head = deleteNode(head, current);  // Elimina il nodo
            if (prev == NULL) {
                current = head;  // Se il nodo eliminato era la testa
            } else {
                prev->next = temp;  // Collega il nodo precedente al successivo
                current = temp;
            }
        } else {
            prev = current;
            current = current->next;  // Passa al nodo successivo
        }
    }

    return head;  // Restituisce la lista modificata
}

// Funzione per scrivere la lista in un file
void writeToFile(Node* head, const char* filename) {
    FILE* file = fopen(filename, "w");  // Apre il file in scrittura
    if (file == NULL) {
        fprintf(stderr, "Errore: Impossibile aprire il file %s per la scrittura\n", filename);
        exit(1);
    }

    Node* current = head;
    while (current != NULL) {  // Scorre la lista
        fputc(current->data, file);  // Scrive il dato di ogni nodo nel file
        current = current->next;
    }

    fclose(file);  // Chiude il file
}

// Funzione per stampare la lista a schermo
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%c", current->data);  // Stampa il dato di ogni nodo
        current = current->next;
    }
    printf("\n");  // Aggiunge una nuova riga alla fine della stampa
}

int main(int argc, char* argv[]) {
    // Decodifica i parametri della riga di comando
    Parameters params = decodeParameters(argc, argv);

    printf("==========PUNTO A==========\n");
    printf("Nome del file di input: %s\n", params.in_filename);
    printf("Nome del file output: %s\n", params.out_filename);
    printf("Valore di c: %c\n", params.c);

    // Legge il file e crea la lista L
    Node* L = readFile(params.in_filename);

    printf("==========PUNTO B==========\n");
    printf("Contenuto della lista:\n");
    printList(L);  // Stampa il contenuto della lista

    // Conta le occorrenze del carattere c
    int o = countOccurrences(L, params.c);
    printf("==========PUNTO C==========\n");
    printf("Occorrenze di %c in L: %d\n", params.c, o);

    // Processa la lista eliminando i nodi che soddisfano la condizione
    L = processL(L, o);
    printf("==========PUNTO D==========\n");
    printf("Contenuto della lista:\n");
    printList(L);  // Stampa la lista processata

    // Scrive la lista nel file di output
    writeToFile(L, params.out_filename);

    // Libera la memoria della lista
    while (L != NULL) {
        L = deleteHead(L);
    }

    return 0;
}
