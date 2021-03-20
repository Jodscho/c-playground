#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define get(M, R, C) (M->values[(R*M->cols)+C])

double at(struct matrix* m, int row, int col){
    return m->values[(row*m->cols)+col];
}

void setat(struct matrix* m, int row, int col, double val){
    m->values[(row*m->cols)+col] = val;
}

void freem(struct matrix* m){
   free(m->values); 
}

struct matrix* create(int rows, int cols, double* vals){
    if(rows < 0 || cols < 0) {
        fprintf(stderr, "negative value for rows/cols");
        exit(1);
    }
    struct matrix *m1 = (struct matrix*) malloc(sizeof(struct matrix));
    m1->rows = rows;
    m1->cols = cols;  
    m1->values = (double*) malloc(sizeof(double) * rows * cols);
    for(int i = 0; i < rows * cols; i++) {
        m1->values[i] = vals[i];
    } 
    return m1;
}

struct matrix* createsymmetric(int rows, int cols, double* vals){
    if(rows != cols) {
        fprintf(stderr, "symmetric matrix needs nxn dimensions");
        exit(1);
    }
    double values[rows * cols];
    int pos = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(j < i){
                continue;
            }
            values[(i*cols)+j] = vals[pos];
            if(i!=j){
                values[(j*cols)+i] = vals[pos];
            }
            pos++;
        }
    }
    return create(rows, cols, values);
}

void print(struct matrix* m){
    int tmp = 0;
    printf("\n");
    for(int i = 0; i < (m->rows * m->cols); i++){
        if(tmp == m->cols){        
            tmp = 0;
            printf("\n");
        }
        printf("%f ", m->values[i]);
        tmp++;
    }
   printf("\n");
}

struct matrix* multiply(struct matrix* m1, struct matrix* m2){
    
    if(m1->cols != m2->rows){
        fprintf(stderr, "invalid dimensions for multiplying: m1-cols: %d, m2-rows: %d", m1->cols, m2->rows);
        exit(1);
    }

    double result[m1->rows*m2->cols];
    for(int i = 0; i < m1->rows; i++){
        for(int k = 0; k < m2->cols; k++){
            result[(i*m2->cols)+k] = 0;
            for(int j = 0; j < m1->cols; j++){
                result[(i*m2->cols)+k] += get(m1, i, j) * get(m2, j, k);
            }
        }
    }
    return create(m1->rows, m2->cols, result);
}

struct matrix* transpose(struct matrix* m){
    double result[m->rows*m->cols];
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            result[(j*m->rows)+i] = get(m, i, j);
        }
    }
    return create(m->cols, m->rows, result);
}

struct matrix* add(struct matrix* m1, struct matrix* m2){

    if(m1->cols != m1->cols || m1->rows != m2->rows){
        fprintf(stderr, "invalid dimensions for addition");
        exit(1);
    }

    double result[m1->rows*m2->cols];
    for(int i = 0; i < m1->rows; i++){
        for(int j = 0; j < m1->cols; j++){
            result[(i*m1->cols)+j] = get(m1, i, j) + get(m2, i, j);
        }
    }
    return create(m1->rows, m1->cols, result);
}

struct matrix* subtract(struct matrix* m1, struct matrix* m2){

    if(m1->cols != m1->cols || m1->rows != m2->rows){
        fprintf(stderr, "invalid dimensions for subtraction");
        exit(1);
    }

    double result[m1->rows*m2->cols];
    for(int i = 0; i < m1->rows; i++){
        for(int j = 0; j < m1->cols; j++){
            result[(i*m1->cols)+j] = get(m1, i, j) - get(m2, i, j);
        }
    }
    return create(m1->rows, m1->cols, result);
}

struct matrix* createzeromatrix(int rows, int cols) {
    double values[rows * cols];
    for(int i = 0; i < rows*cols; i++){
        values[i] = 0;
    }
    return create(rows, cols, values);
}

struct matrix* dividebyfactor(struct matrix* m1, double factor){
    if(factor == 0){
        fprintf(stderr, "cant divide by zero");
        exit(1);
    }
    double result[m1->rows*m1->cols];
    for(int i = 0; i < m1->rows; i++){
        for(int j = 0; j < m1->cols; j++){
            result[(i*m1->cols)+j] = get(m1, i, j) / factor;
        }
    }
    return create(m1->rows, m1->cols, result);
}
struct matrix* multiplybyfactor(struct matrix* m1, double factor){
    double result[m1->rows*m1->cols];
    for(int i = 0; i < m1->rows; i++){
        for(int j = 0; j < m1->cols; j++){
            result[(i*m1->cols)+j] = get(m1, i, j) * factor;
        }
    }
    return create(m1->rows, m1->cols, result);
}

extern struct matrix* colasmatrix(struct matrix* m1, int col){
    double result[m1->rows];
    int tmp = 0;
    for(int i = 0; i < m1->rows; i++){
        for(int j = 0; j < m1->cols; j++){
            if(j != col){
                continue;
            }
            result[tmp++] = get(m1, i, j);
        }
    }
    return create(m1->rows, 1, result);
}
