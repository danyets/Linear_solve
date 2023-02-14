#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "matrix.h"
#include "solving.h"


int main(int argc, char **argv) {
    argc = argc;

    int n, m, k;
    FILE *F = NULL;

    //ввод и проверка корректности введенных данных
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    k = atoi(argv[3]);

    if (n < 1) {
        printf("\nError: incorrect matrix size\n");
        return -1;
    }
    if ((m < -1)) {
        printf("\nError: incorrect output format\n");
        return -1;
    }
    if ((k < 0) || (k > 4)) {
        printf("\nError: incorrect filling parameter\n");
    }

    if (k == 0) {
        F = fopen(argv[4], "r");
    
        if (F == NULL) {
            printf("Error: cannot open file\n");
            return -1;
        }
    }


    //создание матрицы
    double **A;
    bool insert_res;

    if (!(A = (double**)malloc(n * sizeof(double*)))){
        printf("Not enough memory\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        if (!(A[i] = (double*)malloc(n * sizeof(double)))){
            printf("Not enough memory\n");
            while (i != 0) {
                i--;
                free(A[i]);
            }
            free(A);
            return -1;
        }
    }

    if (k != 0) {       //заполнение матрицы по формуле
        matrix_fill(n, k, A);
    }
    else {      //заполнение матрицы данными из файла
        insert_res = matrix_fill_file(n, F, A);
        if (insert_res == false) {
            printf("\nError: incorrect input file\n");
        }
    }


    //создание правой части
    double *b;
    if(!(b = (double*)malloc(n * sizeof(double)))){
        printf("Not enough memory\n");
        for (int i = 0; i < n; i++) {
            free(A[i]);
        }
        free(A);
    }

    //заполнение правой части
    for (int i = 0; i < n; i++) {
        b[i] = 0;
        for (int j = 0; j < n; j += 2) {
            b[i] += A[i][j];
        }
    }
    /*printf("\n");
    printf("\n");
    column_print(n, n, b);
    printf("\n\n");*/



    double *x;      //вектор решения слу
    if (!(x = (double*)malloc(n * sizeof(double)))){
        printf("Not enough memory\n");
        for (int i = 0; i < n; i++) {
            free(A[i]);
        }
        free(A);
        free(b);
    }

    if (m > 0) {        //вывод матрицы, если требуется
            printf("Matrix:");
            printf("\n");
            matrix_print(n, n, m, A);
    }

    int solving;
    double end_time;
    double time;
    double start_time = clock();
    solving = find_solution(n, A, b, x);      //решение слу
    end_time = clock();
    time = end_time - start_time;
    time /= CLOCKS_PER_SEC;

    if (solving == -1){
        printf("Degenerate matrix\n");
        return -1;
    }

    if (m == 0) {
            printf("\n");
            printf("Error: ");
            printf("%10.8e", error(n, x));
            printf("\n");
            printf("Time: ");
            printf("%10.8e", time);
            printf(" sec");
            printf("\n");
            printf("\n");
    }
    else {
        if (m == -1) {
            printf("\n");
            matrix_print(1, n, n, &x);
            printf("\n");
            printf("\n");
        }
        else {
            printf("\n");
            printf("Result:");
            printf("\n");
            matrix_print(1, n, m, &x);
            printf("\n");
            printf("\n");
            printf("Residual: ");
            printf("%10.8e", residual(n, A, b, x));
            printf("\n");
            printf("Error: ");
            printf("%10.8e", error(n, x));
            printf("\n");
            printf("Time: ");
            printf("%.2lf", time);
            printf(" sec");
            printf("\n");
            printf("\n");
        }
    }

    //освобождение ресурсов
    for (int i = 0; i < n; i++) {
        free (A[i]);
    }
    free (A);
    
    free(b);
    free(x);

}




