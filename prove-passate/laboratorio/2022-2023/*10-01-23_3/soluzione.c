/*
    *For scanf, %f reads into a float, and %lf reads into a double.
    *For printf: In C99 and later, they both are identical, and they print either a float or a double. In C89, %lf
     caused undefined behaviour although it was a common extension to treat it as %f.

*/


#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

struct parametri {
    int N;
    float x,y;
};

struct parametri readInput(int argc, char* argv[]){
    if(argc!=4){
        fprintf(stderr, "I parametri sono sbagliati \n");
        exit(-1);
    }

    struct parametri p;

    char **end = malloc(sizeof(char*));

    p.N = (int) strtol(argv[1], end, 0);

    if(!end){
        fprintf(stderr, "'N' deve essere intero \n");
        exit(-1);        
    }

    if(p.N < 10 || p.N > 20){
        fprintf(stderr, "Errore intervallo 'N' \n");
        exit(-1);
    }

    p.x = strtof(argv[2], end);

    if(!end){
        fprintf(stderr, "'x' deve essere float \n");
        exit(-1);        
    }

    p.y = strtof(argv[3], end);

    if(!end){
        fprintf(stderr, "'y' deve essere float \n");
        exit(-1);        
    }

    if(p.x < 5 || p.x > 30 || p.y < 5 || p.y > 30){
        fprintf(stderr, "Errore intervalli 'x e y' \n");
        exit(-1);
    }
    
    if(p.x >= p.y){
        fprintf(stderr, "Errore 'x' deve essere maggiore di 'y' \n");
        exit(-1);
    }

    return p;
}

double genDouble(float x, float y){
    return ((double) get_random() / UINT_MAX) * (y-x)+x;
}

double **genMatrix(int N, float x, float y){
    double **A = calloc(N, sizeof(double*));

    for(int i=0; i<N; i++){
        A[i] = calloc(N, sizeof(double));

        for(int j=0; j<N; j++){
            A[i][j] = genDouble(x, y);
        }
    }

    return A;
}

int computeMinMax(double **A, int N, double *mind, double *maxd){
    *mind = A[0][0];
    *maxd = A[N-1][0];

    for(int i=0; i<N; i++){
        if(A[i][i] < *mind) // diagonale principale
            *mind = A[i][i];

        if(A[i][N-1-i] > *maxd)
            *maxd = A[i][N-1-i]; // diagonale secondaria
    }

    int count = 0;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(A[i][j] <= *maxd && A[i][j] >= *mind)
                count++;
        }
    }

    return count;
}

double *createArray(double **A, int N, int num, double mind, double maxd){
    double *out = calloc(num, sizeof(double));

    int indice = 0;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(A[i][j] <= maxd && A[i][j] >= mind)
                out[indice++] = A[i][j];
        }
    }

    return out;
}

// selection sort
void sortArray(double array[], int num){
    for(int i=0; i<num-1; i++){
        int smallest = i;
        for(int j=i+1; j<num; j++){
            if(array[j] < array[smallest])
            smallest = j;
        }
    double tmp = array[i];
    array[i] = array[smallest];
    array[smallest] = tmp;
    }
}


void printArray(double array[], int num){
    double mean = 0;

    for(int i=0; i<num; i++){
        printf("%f\n", array[i]);
        mean += array[i];
    }
    mean /= num;

    printf("Media e': %f\n", mean);
}

int main(int argc, char* argv[]){
    struct parametri p = readInput(argc, argv);
    double **A = genMatrix(p.N, p.x, p.y);

    double mind, maxd;

    int num = computeMinMax(A, p.N, &mind, &maxd);
    double *array = createArray(A, p.N, num, mind, maxd);

    sortArray(array, num);
    printArray(array, num);
}






