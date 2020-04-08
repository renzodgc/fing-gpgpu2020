#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define TIME(t_i,t_f) ((double) t_f.tv_sec * 1000.0 + (double) t_f.tv_usec / 1000.0) - \
                      ((double) t_i.tv_sec * 1000.0 + (double) t_i.tv_usec / 1000.0);

void random_matriz(float **A, int m, int n) {
    for (unsigned int i = 0; i < m; i++) 
        for (unsigned int j = 0; j < n; j++) 
                A[i][j] = (float)rand() / (float)RAND_MAX;
}

/* Ej A)
*   Construir la multiplicacion de matrices con el patron de acceso usual (computando C_{ij} antes de avanzar a la siguiente).
*   Las matrices no tienen porque ser cuadradas.
*/
void mult_simple(float ** A, float ** B, float ** C, int m, int p, int n) {

} 

/* Ej B)
*   Construir la multiplicacion de matrices que acceda por fila tanto a la matriz A como a la matriz B (en lugar de por columna a B)
*   Las matrices no tienen porque ser cuadradas.
*/
void mult_porfilas(float ** A, float ** B, float ** C, int m, int p, int n) {

} 

/* Ej C)
*   Construir la multiplicacion de matrices "por bloques" de tamanio variable (nb = 64, 128, 256, 512)
*   Las matrices no tienen porque ser cuadradas.
*/
void mult_porbloques(float ** A, float ** B, float ** C, int m, int p, int n, int nb) {

} 

int main(int argc, char *argv[]){

    int n = 512, m = 512, p = 512, nb=16;
    
    if (argc < 5) {
       printf("Uso: ./Ej3 n m p nb \n");
       exit(1);
    }

    if(argc == 5){
        m  = atoi(argv[1]);
        n  = atoi(argv[2]);
        p  = atoi(argv[3]);
        nb = atoi(argv[4]);
    }
        
    float ** A, **B, **C; 
    
    A = (float**) malloc(m*sizeof(float*));
    for (int i = 0; i < m; ++i) A[i] = (float*) malloc(p*sizeof(float)); 

    B = (float**) malloc(p*sizeof(float*));
    for (int i = 0; i < p; ++i) B[i] = (float*) malloc(n*sizeof(float)); 

    C = (float**) malloc(m*sizeof(float*));
    for (int i = 0; i < m; ++i) C[i] = (float*) malloc(n*sizeof(float)); 


    srand(0); // Inicializa la semilla aleatoria
    random_matriz(A,m,p);
    random_matriz(B,p,n);

    struct timeval t_i, t_f;

    gettimeofday(&t_i, NULL);
    mult_simple(A,B,C,m,p,n);
    gettimeofday(&t_f, NULL);
    double t_gemm_simple = TIME(t_i,t_f);

    gettimeofday(&t_i, NULL);
    mult_porfilas(A,B,C,m,p,n);
    gettimeofday(&t_f, NULL);
    double t_gemm_fil = TIME(t_i,t_f);

    gettimeofday(&t_i, NULL);
    mult_porbloques(A,B,C,m,p,n,nb);
    gettimeofday(&t_f, NULL);
    double t_gemm_bloq = TIME(t_i,t_f);

    printf("Tamanho: (%i,%i,%i,%i) Tiempo fila:    %f ms\n", m, n, p, nb, t_gemm_simple);
    printf("Tamanho: (%i,%i,%i,%i) Tiempo fila:    %f ms\n", m, n, p, nb, t_gemm_fil   );
    printf("Tamanho: (%i,%i,%i,%i) Tiempo columna: %f ms\n", m, n, p, nb, t_gemm_bloq  );

    for (int i = 0; i < m; ++i) free(A[i]);
    free(A);

    for (int i = 0; i < p; ++i) free(B[i]);
    free(B);

    for (int i = 0; i < n; ++i) free(C[i]);
    free(C);

	return 0;
}
