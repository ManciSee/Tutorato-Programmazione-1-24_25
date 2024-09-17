/*
    * malloc() is used to allocate memory blocks of a specific size, 
    * calloc() is used to allocate memory blocks of a specific size and initializes the memory with zero.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

struct data {
    int k, N, M;
    char w;
};

// Punto A
struct data readInput(char *argv[], int argc){
    if(argc != 5){
        fprintf(stderr, "I parametri non sono validi");
        exit(-1);
    }

    struct data d = {0,0,0,0};

    char **end = malloc(sizeof(char*));
    *end = NULL;

    d.k = (int) strtol(argv[1], end, 0);
    //d.k = atoi(argv[1]);

    if(**end){
        fprintf(stderr, "Il k deve essere intero");
        exit(-1);
    }

    if(d.k<10 || d.k>15){
        fprintf(stderr, "Il k deve essere compreso tra 10 e 15");
        exit(-1);
    }

    if(strlen(argv[2])!=1){
        fprintf(stderr, "w è vuoto!");
        exit(-1);
    }

    d.w = argv[2][0];

    if(d.w<'a' || d.w>'z'){
        fprintf(stderr, "Il w deve essere compreso tra 'a' e 'z' ");
        exit(-1);
    }

    d.N = (int) strtol(argv[3],end,0);
    //d.N = atoi(argv[3]);

    if(**end){
        fprintf(stderr, "N deve essere intero");
        exit(-1);
    }

    if(d.N<4 || d.N>8){
        fprintf(stderr, "N deve essere compreso tra 4 e 8");
        exit(-1);
    }
    d.M = (int) strtol(argv[4], end, 0);
    //d.M = atoi(argv[4]);

    if(**end){
        fprintf(stderr, "M deve essere intero");
        exit(-1);
    }

    if(d.M<4 || d.M>8){
        fprintf(stderr, "M deve essere compreso tra 4 e 8");
        exit(-1);
    }

    return d;
}

// Punto B
char*** allocateS(int N, int M){
    char ***S = calloc(N, sizeof(char**));
    for(int i=0; i<N; i++){
        S[i] = calloc(M, sizeof(char*));
    }
    return S;
}

// Punto C
char* genString(int len, char min, char max){
    char *s = calloc(len, sizeof(char*));

    for(int i=0; i<len; i++){
        s[i] = get_random() % (max-min+1) + min;
    }

    return s;
}

void fillS(char ***S, int N, int M, int k){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            S[i][j] = genString(k, 'a', 'z');
        }
    }
}

// Punto D - bubblesort
void sortS(char ***S, int N, int M){
    for(int j=0; j<M; j++){
        for(int pass=0; pass<N-1; pass++){
            for(int i=0; i<N-1-pass; i++){
                if(strcmp(S[i][j], S[i+1][j]) > 0){
                    char *tmp = S[i][j];
                    S[i][j] =  S[i+1][j];
                    S[i+1][j] = tmp;
                }
            }
        }
    }
}

// Punto E
void printMatrix(char ***S, int N, int M){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            printf("%s ", S[i][j]);
        }
        printf("\n");
    }
}

// Punto F
int conta(char* s, char w){
    int c = 0;
    for(int i=0; i<strlen(s); i++){
        if(s[i]==w)
            c++;
    }
    return c;
}

void printMax(char ***S, int N, int M, char w){
    //int max = 0;
    int max = 0;
    int i_max = 0;
    int j_max = 0;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            int contatore = conta(S[i][j], w);
            if(contatore > max){
                max = contatore;
                i_max = i;
                j_max = j;
            }
        }
    }

    printf("\n Stringa con %d occorrenze di '%c' trovata agli indici %d,%d: ", max, w, i_max, j_max);

    for(int i=0; i<strlen(S[i_max][j_max]); i++){
        char c = S[i_max][j_max][i];
        c = (c==w) ? '*' : c;
        printf("%c", c);
    }
    printf("\n");
}

// main
int main(int argc, char* argv[]){
    struct data d = readInput(argv, argc);
    char ***S = allocateS(d.N, d.M);
    fillS(S, d.N, d.M, d.k);
    sortS(S, d.N, d.M);
    printMatrix(S, d.N, d.M);
    printMax(S, d.N, d.M, d.w);
}
