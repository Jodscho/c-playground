#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define get(M, R, C) (M->values[(R*M->cols)+C])

struct matrix* create(int rows, int cols, float* vals){
    struct matrix *m1 = (struct matrix*) malloc(sizeof(struct matrix));
    m1->rows = rows;
    m1->cols = cols;  
    m1->values = (float*) malloc(sizeof(float) * rows * cols);
    for(int i = 0; i < rows * cols; i++) {
        m1->values[i] = vals[i];
    } 
    return m1;
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
    float result[m1->rows*m2->cols];
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
    float result[m->rows*m->cols];
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            result[(j*m->rows)+i] = get(m, i, j);
        }
    }
    return create(m->cols, m->rows, result);
}

struct matrix* add(struct matrix* m1, struct matrix* m2){
    float result[m1->rows*m2->cols];
    for(int i = 0; i < m1->rows; i++){
        for(int j = 0; j < m1->cols; j++){
            result[(i*m1->cols)+j] = get(m1, i, j) + get(m2, i, j);
        }
    }
    return create(m1->rows, m1->cols, result);
}
