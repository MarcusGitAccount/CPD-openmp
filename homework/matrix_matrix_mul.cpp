#include "omp.h"
#include <iostream>

#define SIZE 10

int main(void) {
    float A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    int i, j, k, tid;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++) {
            A[i][j] = B[i][j] = (j + 1) * 1.0f;
        }

    }

    printf("\nStarting values of matrix A and vector b:\n");

    for (i = 0; i < SIZE; i++)
    {
        printf(" A[%d] = B[%d] = ", i, i);
        for (j = 0; j < SIZE; j++) {
            printf("%.1f ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nResults by thread/row:\n");

/* Create a team of threads and scope variables */
// #pragma omp for private(j, k)
    #pragma omp parallel for private(i,j,k) shared(A,B,C)

    for (i = 0; i < SIZE; i++) 
    {
        // printf("I'm thread %d in loop i = %d\n", omp_get_thread_num(), i);
        for (j = 0; j < SIZE; j++)
        {
            C[i][j] = 0.0f;
            for (k = 0; k < SIZE; k++) {
                C[i][j] += (A[i][k] * B[k][j]);
            }

            // printf("I'm thread %d in loop j = %d\n", omp_get_thread_num(), i);
        }
    }

    for (i = 0; i < SIZE; i++)
    {
        printf(" C[%d] = ", i, i);
        for (j = 0; j < SIZE; j++) {
            printf("%.1f ", C[i][j]);
        }
        printf("\n");
    }

}