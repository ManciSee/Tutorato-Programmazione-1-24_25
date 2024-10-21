#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct parametri{
    char input[255];
    char output[255];
};

struct parametri readParameters(int argc, char* argv[]){

    if(argc != 3){
        fprintf(stderr, "Il numero dei paramtri deve essere '3'.\n");
        exit(-1);
    }

    struct parametri p;
    strcpy(p.input, argv[1]);
    strcpy(p.output, argv[2]);

    return p;
}

float*** createMatrix(char filename[], int* n, int* m){
    FILE *f = fopen(filename, "r");

    if(f == NULL){
        fprintf(stderr, "Impossibile aprire il file %s \n", filename);
        exit(-1);
    }

    char s[1000];
    char *end;

    *n = 0;
    *m = 0;

    do {
        end = fgets(s, 1000, f);
        (*n)++;
        if(*m == 0){
            char *tok;
            char *tmp = s;
            do {
                tok = strtok(tmp, " \n");
                tmp = NULL;
                (*m)++;
            } while(tok);
        }
    } while(end);

    (*n)--;
    (*m)--;

    fseek(f, 0, 0);


    float ***A = calloc(*n, sizeof(float**));
    for(int i=0; i < *n; i++){
        A[i] = calloc(*m, sizeof(float*));
        for(int j=0; j< *m; j++){
            A[i][j] = NULL;
        }
    }

    for(int i=0; i < *n; i++){
        end = fgets(s, 1000, f);
        char *tok;
        char *tmp = s;


        for(int j=0; j < *m; j++){
            tok = strtok(tmp, " \n");
            tmp = NULL;

            if(tok){
                char **e = malloc(sizeof(char*));
                A[i][j] = malloc(sizeof(float));
                *(A[i][j]) = strtof(tok, e);
                free(e);
            }
        }
    }
    return A;
}

void sparsify(float ***A, int n, int m){
    for(int i=0; i<n; i++){
        float mean = 0;
        int count = 0;
        for(int j=0; j<m; j++){
            if(A[i][j]){
                mean += *A[i][j];
                count++;
            }
        }
        mean /= count;

        for(int j=0; j<m; j++){
            if(A[i][j] && *A[i][j] > mean){
                float *tmp = A[i][j];
                A[i][j] = NULL;
                free(tmp);
            }
        }
    }
}

float *collect(float ***A, int n, int m, int* num){
    *num = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(A[i][j])
                (*num)++;
        }
    }

    float *out = calloc(*num, sizeof(float));

    int c = 0;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(A[i][j])
                out[c++] = *A[i][j];
        }
    }

    return out;
}

void writeToFile(char output[], float *array, int n){
    FILE *f = fopen(output, "w");

    for(int i=0; i<n; i++){
        fprintf(f, "%5.2f\n", array[i]);
    }
}

int main(int argc, char* argv[]){
    struct parametri p = readParameters(argc, argv);

    int N, M;
    float ***A = createMatrix(p.input, &N, &M);
    sparsify(A, N, M);
    
    int num;
    float *out = collect(A, N, M, &num);
    
    writeToFile(p.output, out, num);
}
