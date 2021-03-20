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

struct matrix* identity(int rows){
    double values[rows*rows];
    for(int i = 0; i < rows*rows; i++){
        values[i] = (i % (rows+1) == 0) ? 1 : 0;
    }
    return create(rows, rows, values);
}

struct matrix* inverse(struct matrix* m){

    if(m->rows != m->cols) {
        fprintf(stderr, "matrix needs to be symmetric");
        exit(1);
    }
    
    if(m->rows > 3){
        fprintf(stderr, "inverse can only be computed for dimensions <= 3");
        exit(1);
    }

    double factor = 1/determinant(m);
    double values[m->rows*m->cols];

    if(m->rows == 3){
        double a = at(m,0,0);
        double b = at(m,0,1);
        double c = at(m,0,2);
        double d = at(m,1,0);
        double e = at(m,1,1);
        double f = at(m,1,2);
        double g = at(m,2,0);
        double h = at(m,2,1);
        double i = at(m,2,2);
        values[0] = (e*i-f*h)*factor;
        values[1] = (c*h-b*i)*factor;
        values[2] = (b*f-c*e)*factor;
        values[3] = (f*g-d*i)*factor;
        values[4] = (a*i-c*g)*factor;
        values[5] = (c*d-a*f)*factor;
        values[6] = (d*h-e*g)*factor;
        values[7] = (b*g-a*h)*factor;
        values[8] = (a*e-b*d)*factor;
    } else if(m->rows == 2){
        values[0] = at(m,1,1)*factor;
        values[1] = -1*at(m,0,1)*factor;
        values[2] = -1*at(m,1,0)*factor;
        values[3] = at(m,0,0)*factor; 
    }
    return create(m->rows, m->cols, values);
}


double determinant(struct matrix* m){

    if(m->rows != m->cols) {
        fprintf(stderr, "matrix needs to be symmetric");
        exit(1);
    }
    
    if(m->rows > 3){
        fprintf(stderr, "determinant can only be computed for dimensions <= 3");
        exit(1);
    }

    if(m->rows == 2){
        return at(m, 0, 0) * at(m, 1, 1) - at(m, 1, 0) * at(m, 0, 1);
    } else if(m->rows == 3){
        return  at(m,0,0)*at(m,1,1)*at(m,2,2)
              + at(m,0,1)*at(m,1,2)*at(m,2,0)
              + at(m,0,2)*at(m,1,0)*at(m,2,1)
              - at(m,2,0)*at(m,1,1)*at(m,0,2)
              - at(m,2,1)*at(m,1,2)*at(m,0,0)
              - at(m,2,2)*at(m,1,0)*at(m,0,1);
    }
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
