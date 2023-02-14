#ifndef MATRIX_H
#define MATRIX_H

void matrix_fill(int n, int k, double **A);
double f(int k, int n, int i, int j);
bool matrix_fill_file(int n, FILE* F, double **A);

bool matrix_print(int l, int n, int m, double **A);
//bool column_print(int n, int l, double *x);

double residual(int n, double **A, double *b, double *x);
double error(int n, double *x);

#endif


