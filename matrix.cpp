#include <math.h>
#include <stdio.h>

#include "matrix.h"

void matrix_fill(int n, int k, double **A) {        //заполнение матрицы по формулам
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = f(k, n, i + 1, j + 1);
        }
    }

    return;
}

double f(int k, int n, int i, int j) {      //формулы заполнения матрицы
    if (k == 1) {
        return n - (i + j + fabs(i - j))/2 + 1;
    }
    if (k == 2) {
        return (i + j + fabs(i - j))/2;
    }
    if (k == 3) {
        return fabs(i - j);
    }
    if (k == 4) {
        return 1.0/(i + j - 1);
    }

    return 0;
}




bool matrix_fill_file(int n, FILE* F, double **A) {     //заполнение матрицы данными из файла

    rewind(F);

    double d;
    int counter_of_numbers = 0;
   
    while (fscanf(F, "%lf", &d) == 1) {     //подсчет количества чисел в файле
        counter_of_numbers++;
    }
    if (counter_of_numbers != n*n) {        //проверка количества чисел в файле
        return false;
    }

    //непосредственно заполнение матрицы
    rewind(F);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(F, "%lf", &d);
            A[i][j] = d;
        }
    }

    return true;
}



//вывод фрагмента матрицы
bool matrix_print(int l, int n, int m, double **A) {
    for (int i = 0; (i < m) && (i < l); i++) {
        for (int j = 0; (j < m) && (j < n); j++) {
            printf(" ");
            printf("%10.8e", A[i][j]);
        }
        printf("\n");
    }

    return true;
}




//вычисление нормы невязки
double residual(int n, double **A, double *b, double *x) {
    double help_sum;
    double final_sum = 0;
    for (int i = 0; i < n; i++) {
        help_sum = b[i];
        help_sum *= -1;
        for (int j = 0; j < n; j++) {
            help_sum += A[i][j]*x[j];
        }
        
        final_sum += help_sum * help_sum;
    }

    final_sum = sqrt(final_sum);

    help_sum = 0;
    for (int i = 0; i < n; i++) {
        help_sum += b[i] * b[i];
    }
    help_sum = sqrt(help_sum);

    final_sum /= help_sum;

    return final_sum;
}

//вычисление нормы погрешности
double error(int n, double *x) {
    double sum = 0;
    int iter = 1;
    for (int i = 0; i < n; i++) {
        sum += (x[i] - iter) * (x[i] - iter);
        if (iter == 1) {
            iter = 0;
        }
        else {
            iter = 1;
        }
    }
    sum = sqrt(sum);

    return sum;
}
