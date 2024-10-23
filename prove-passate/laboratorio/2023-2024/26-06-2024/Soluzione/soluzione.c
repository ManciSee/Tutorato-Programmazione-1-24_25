#include <stdio.h>   // Libreria standard per input/output
#include <stdlib.h>  // Libreria standard per gestione memoria dinamica e altre utility
#include <string.h>  // Libreria per la gestione delle stringhe
#include <time.h>    // Libreria per la gestione del tempo e della randomizzazione
#include <stdbool.h> // Libreria per il tipo booleano (true/false)

// Struct per i parametri passati tramite linea di comando
typedef struct {
    char *inputFile;  // Nome del file di input
    int n;            // Valore intero n, utilizzato in vari calcoli
    char *outputFile; // Nome del file di output
    char *alfabeto;   // Stringa con l'alfabeto specificato nel file di input
} Parameters;

// Struttura nodo per una coda (queue) collegata
struct queueNode {
    char *data;            // Dati (una stringa) contenuti nel nodo
    struct queueNode *next; // Puntatore al nodo successivo
};

typedef struct queueNode QueueNode; // Alias per la struttura queueNode

// Funzione per copiare una stringa dinamicamente
char* myStringCopy(char* inputString) {
    // Alloca un array di caratteri della lunghezza della stringa +1 (per il terminatore '\0')
    char* out = calloc(strlen(inputString)+1, sizeof(char));

    if(out) { // Verifica se l'allocazione della memoria è riuscita
        // Copia la stringa di input nella nuova stringa
        strcpy(out, inputString);
    }
    return out; // Restituisce il puntatore alla nuova stringa
}

// Funzione che controlla se la coda è vuota
bool isEmpty(QueueNode *head) {
    return head == NULL; // Ritorna true se la testa è NULL (coda vuota)
}

// Stampa gli elementi della coda
void printQueue(QueueNode *head) {
    QueueNode *aux = head; // Inizializza un puntatore ausiliario al primo elemento della coda
    while (aux) {          // Itera finché ci sono elementi nella coda
        printf("%s\n", aux->data); // Stampa la stringa del nodo corrente
        aux = aux->next;           // Passa al nodo successivo
    }
}

// Funzione per inserire un elemento alla fine della coda
bool enqueue(QueueNode **head, QueueNode **tail, char* data) {
    QueueNode *newNode = malloc(sizeof(QueueNode)); // Alloca un nuovo nodo

    if (newNode == NULL) // Verifica se l'allocazione è riuscita
        return false;


    // ! cambiare con strncpy !
    newNode->data = myStringCopy(data); // Copia i dati nel nuovo nodo
    newNode->next = NULL; // Il nuovo nodo non ha successivi (è la coda)

    if (isEmpty(*head)) { // Se la coda è vuota
        *head = newNode;  // Il nuovo nodo diventa sia la testa che la coda
    } else {
        (*tail)->next = newNode; // Altrimenti, collega il nuovo nodo alla fine della coda
    }

    *tail = newNode; // Aggiorna il puntatore alla coda (tail)

    return true; // Inserimento riuscito
}

// Funzione per rimuovere un elemento dalla testa della coda
char* dequeue(QueueNode **head, QueueNode **tail) {
    if (isEmpty(*head)) // Se la coda è vuota
        return NULL;    // Non è possibile rimuovere nulla

    char* data = (*head)->data; // Salva i dati del nodo da rimuovere
    QueueNode *tmp = *head;     // Memorizza il nodo da eliminare
    *head = (*head)->next;      // La nuova testa diventa il nodo successivo

    if (*head == NULL) // Se la coda è ora vuota
        *tail = NULL;  // Anche la coda diventa NULL

    free(tmp);         // Libera la memoria del nodo rimosso
    return data;       // Restituisce i dati del nodo rimosso
}

// Funzione per la generazione di numeri casuali
unsigned int get_random() {
    // Variabili statiche per generazione di numeri casuali
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w; // Restituisce il numero casuale generato
}

// Funzione per decodificare i parametri passati da riga di comando
Parameters decodeParameters(int argc, char *argv[]) {
    Parameters params;

    if (argc != 4) { // Verifica che ci siano esattamente 3 argomenti (oltre il nome del programma)
        fprintf(stderr, "Usage: %s <input file> <integer n> <output file>\n", argv[0]);
        exit(1);
    }

    params.inputFile = argv[1]; // Assegna il nome del file di input
    params.n = atoi(argv[2]);   // Converte il secondo argomento in intero
    params.outputFile = argv[3]; // Assegna il nome del file di output

    if (params.n < 3 || params.n > 12) { // Verifica che n sia tra 3 e 12
        fprintf(stderr, "Error: n must be between 3 and 6.\n");
        exit(2);
    }

    FILE *file = fopen(params.inputFile, "r"); // Apre il file di input in modalità lettura
    if (!file) { // Verifica che il file sia stato aperto correttamente
        fprintf(stderr, "Error: Cannot open input file.\n");
        exit(3);
    }

    params.alfabeto = calloc(255, sizeof(char)); // Alloca memoria per la stringa dell'alfabeto

    fscanf(file, "%s", params.alfabeto); // Legge la stringa dal file di input
    size_t len = strlen(params.alfabeto); // Calcola la lunghezza dell'alfabeto
    if (len < 8 || len > 12) { // Verifica che la lunghezza sia tra 8 e 12 caratteri
        fprintf(stderr, "Error: Input string must be between 8 and 12 characters.\n");
        exit(5);
    }

    return params; // Restituisce i parametri
}

// Funzione per calcolare la sequenza di Fibonacci
void fibonacci(int n, int *A) {
    if (n >= 1) A[0] = 0; // Il primo numero di Fibonacci è 0
    if (n >= 2) A[1] = 1; // Il secondo numero di Fibonacci è 1
    for (int i = 2; i < n; ++i) {
        A[i] = A[i-1] + A[i-2]; // Ogni numero successivo è la somma dei due precedenti
    }
}

// Funzione per generare una stringa casuale data una lunghezza e un alfabeto
void sampleString(const char *alphabet, int length, char *result) {
    size_t alphabet_len = strlen(alphabet); // Lunghezza dell'alfabeto
    for (int i = 0; i < length; ++i) {
        result[i] = alphabet[get_random() % alphabet_len]; // Genera un carattere casuale dall'alfabeto
    }
    result[length] = '\0'; // Termina la stringa con il carattere NULL
}

// Funzione per creare un array di stringhe basato sulla sequenza di Fibonacci
void getStringArray(int *A, int n, const char *alphabet, char **B) {
    for (int i = 0; i < n; ++i) {
        B[i] = (char *)malloc((A[i] + 1) * sizeof(char)); // Alloca memoria per ogni stringa
        sampleString(alphabet, A[i], B[i]); // Genera una stringa casuale con lunghezza A[i]
    }
}

// Funzione che gestisce l'inserimento di stringhe nella coda
void getQueue(char **B, int n, QueueNode **head, QueueNode **tail) {
    for (int i=0; i<n; i++) {
        if(i==0) {
            enqueue(head, tail, B[i]); // Inserisce la prima stringa nella coda
        } else {
            if (strlen(B[i]) % 2 != 0) { // Se la lunghezza della stringa è dispari
                char *str = dequeue(head, tail); // Rimuove una stringa dalla testa della coda
                char *newstr = calloc(strlen(str) + strlen(B[i]), sizeof(char)); // Alloca memoria per una nuova stringa
                strcat(newstr, B[i]); // Combina la nuova stringa con quella rimossa dalla coda
                strcat(newstr, str);
                enqueue(head, tail, newstr); // Inserisce la stringa combinata nella coda
                free(str); // Libera la memoria
                free(newstr);
            } else { // Se la lunghezza è pari
                enqueue(head, tail, B[i]); // Inserisce la stringa nella coda
            }
        }
    }
}

// Funzione per scrivere il contenuto della coda su file
void writeToFile(const char *outputFile, QueueNode **head, QueueNode **tail) {
    FILE *file = fopen(outputFile, "w"); // Apre il file di output in modalità scrittura
    if (!file) { // Verifica che il file sia stato aperto correttamente
        fprintf(stderr, "Error: Cannot open output file.\n");
        exit(6);
    }
    while (!isEmpty(*head)) { // Finché la coda non è vuota
        fprintf(file, "%s\n", dequeue(head, tail)); // Scrive ogni stringa su file
    }
    fclose(file); // Chiude il file
}

int main(int argc, char *argv[]) {
    Parameters params = decodeParameters(argc, argv); // Decodifica i parametri passati da linea di comando

    printf("========================A========================\n");
    printf("Parameters: inputFile=%s, n=%d, outputFile=%s\n", params.inputFile, params.n, params.outputFile);
    printf("Input string: %s\n", params.alfabeto);

    int A[params.n]; // Array per la sequenza di Fibonacci
    fibonacci(params.n, A); // Calcola la sequenza di Fibonacci

    printf("========================B========================\n");
    printf("Fibonacci array: ");
    for (int i = 0; i < params.n; ++i) {
        printf("%d ", A[i]); // Stampa l'array di Fibonacci
    }
    printf("\n");

    char *B[params.n]; // Array di stringhe
    getStringArray(A, params.n, params.alfabeto, B); // Genera l'array di stringhe

    printf("========================C========================\n");
    printf("String array B:\n");
    for (int i = 0; i < params.n; ++i) {
        printf("%s\n", B[i]); // Stampa l'array di stringhe
    }

    printf("========================D========================\n");
    puts("Queue:");
    QueueNode *head = NULL; // Inizializza la coda vuota
    QueueNode *tail = NULL;
    getQueue(B, params.n, &head, &tail); // Inserisce le stringhe nella coda

    printQueue(head); // Stampa il contenuto della coda

    writeToFile(params.outputFile, &head, &tail); // Scrive la coda su file

    for (int i = 0; i < params.n; ++i) {
        free(B[i]); // Libera la memoria delle stringhe
    }

    return 0; // Termina il programma
}
