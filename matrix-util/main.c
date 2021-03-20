#include "matrix.h"
#include <stdio.h>

int main() {

    double vals1[] = {2,-1,0,-1,2,-1,0,-1,2};
    double vals2[] = {1,2,3,4};
    struct matrix* m1 = create(3, 3, vals1);
    struct matrix* m2 = create(2, 2, vals2);

    print(m1);
    //print(m2);
    //print(multiply(m1, m2));
    //print(transpose(m1));
    //print(add(m1, transpose(m1)));
    //print(identity(5));
    //print(identity(5));
    //printf("%f\n",determinant(m1));
    print(inverse(m1));
    print(inverse(m2));

}
