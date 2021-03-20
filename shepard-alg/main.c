#include "../matrix-util/matrix.h"
#include <math.h>
#include <stdio.h>

struct matrix* computedistancematrix(struct matrix* x){
    double vals[x->cols * x->cols]; 
    int total = 0;
    for(int i = 0; i < x->cols; i++){ 
        for(int j = i; j < x->cols; j++){ 
            double result = 0;
            for(int k = 0; k < x->rows; k++){ 
                double first = at(x, k, i);
                double second = at(x, k, j);
                result += pow(first - second, 2);
            }
            vals[total++] = sqrt(result); 
        }   
    }
    
    return createsymmetric(x->cols, x->cols, vals);
}

double discrepencyindex(struct matrix* d, struct matrix* dhat){
    double value = 0;
    int n = d->rows;
    for(int i = 0; i < d->rows; i++){ 
        for(int j = i; j < d->cols; j++){ 
            double dij = at(d, i, j); 
            double dhatij = at(dhat, i, j); 
            value += pow(dij - dhatij, 2);
        }
    }
    return (2*value)/(n*(n-1));
}


int main(){

    double d_vals[] = {0,1,7,6,5,0,5,4,3,0,1,1,0,1,0}; 
    double x0_vals[] = {4,4,4,1,7,7,-1,3,3,3}; 
    double bbar = 8;
    double bs = 0;
   
    // step 1: initialization
    struct matrix* d = createsymmetric(5, 5, d_vals); // product similarity
    struct matrix* x0 = create(2, 5, x0_vals); // start configuration
    
    do{
        // step 2: distance matrix between product attributes (product attribute similarity)
        struct matrix* dhat = computedistancematrix(x0); 

        // step 3: calc discrepencyindex
        bs = discrepencyindex(d, dhat);

        // step 4: difference between actual product similarity and product attribute similarity
        struct matrix* w0 = subtract(d, dhat);

        // step 5: calc direction in which to move products
        struct matrix* x0_tilde[dhat->rows][dhat->cols];
        for(int i = 0; i < dhat->rows; i++){
            for(int j = 0; j < dhat->cols; j++){
                
                if(i == j){
                    x0_tilde[i][j] = createzeromatrix(x0->rows, 1);
                } else {
                    
                    struct matrix* x0i = colasmatrix(x0, i);
                    struct matrix* x0j = colasmatrix(x0, j);
                    struct matrix* subtr = subtract(x0i, x0j);
                    x0_tilde[i][j] = dividebyfactor(subtr, at(dhat, i, j));
                    freem(x0i);
                    freem(x0j);
                    freem(subtr);
                }
            }
        }

        // weigh the amount by which the product is moved
        struct matrix* xv_tilde[dhat->rows][dhat->cols];
        for(int i = 0; i < dhat->rows; i++){
            for(int j = 0; j < dhat->cols; j++){
                xv_tilde[i][j] = multiplybyfactor(x0_tilde[i][j], at(w0, i, j));
            }
        }
   
        // step 6: calculate new product configuration
        struct matrix* result = createzeromatrix(x0->rows, x0->cols);
        for(int i = 0; i < dhat->rows; i++){
            struct matrix* xi = colasmatrix(x0, i);
            for(int k = 0; k < x0->rows; k++){
                double sum = 0;
                for(int j = 0; j < dhat->cols; j++){
                    if(i == j){
                        sum += at(xi, k, 0);
                        continue;
                    }
                    struct matrix* vec = xv_tilde[i][j];
                    sum += at(vec, k, 0);
                }
                setat(result, k, i, sum);
            }
            freem(xi);
        }
        
        //print(result);
        freem(x0);
        x0 = result;

        // cleanup
        freem(dhat);
        freem(w0);
        for(int i = 0; i < dhat->rows; i++){
            for(int j = 0; j < dhat->cols; j++){
                freem(xv_tilde[i][j]);
                freem(x0_tilde[i][j]);
            }
        }

        printf("bbar: %f, bs: %f\n", bbar, bs);
    } while(bs >= bbar);
}
