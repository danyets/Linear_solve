#include <stdio.h>
#include <math.h>

#include "matrix.h"
#include "solving.h"

int find_solution(int n, double **A, double *b, double* x) {
    const int epsilon = 1.0e-37;

    int index_of_main;
    double main_value;
    double element;
    for (int i = 0; i < n; i++) {       //i - индекс (нумерация ведется с 0) первого столбца, в котором главный элемент ещё не искался
        index_of_main = i;
        for (int j = i+1; j < n; j++) {     //поиск главного элемента по столбцу
            if (fabs(A[index_of_main][i]) < fabs(A[j][i])) {
                index_of_main = j;
            }
        }

        if (fabs(A[index_of_main][i]) < epsilon) {      //проверка равенства нулю главного элемента
            return -1;
        }


        main_value = A[index_of_main][i];
        if (fabs(main_value - 1) > epsilon){
            for (int j = i; j < n; j++) {       //сокращение строки с главным элементом на его значение
                A[index_of_main][j] /= main_value;
            }
            b[index_of_main] /= main_value;
        }

        if (i != index_of_main) {
            for (int j = i; j < n; j++) {       //перестановка местами строки с индексом i и строки с главным элементом
                element = A[i][j];
                A[i][j] = A[index_of_main][j];
                A[index_of_main][j] = element;
            }
            element = b[i];
            b[i] = b[index_of_main];
            b[index_of_main] = element;
        }

        for (int j = i+1; j < n; j++) {     //обращение в нуль всех элементов i-го столбца, которые стоят ниже строки индексом index_current
            main_value = A[j][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= main_value * A[i][k];
            }
            b[j] -= main_value * b[i];
        }
    }

    x[n-1] = b[n-1];
    for (int i = n-2; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= x[j] * A[i][j];
        }
    }

    return 0;
}
