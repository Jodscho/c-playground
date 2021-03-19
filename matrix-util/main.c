#include "matrix.h"

int main() {

    float vals1[] = {1,5,3,2};
    float vals2[] = {1,2,3,4,5,6};
    struct matrix* m1 = create(2, 2, vals1);
    struct matrix* m2 = create(2, 3, vals2);

    print(m1);
    print(m2);
    print(multiply(m1, m2));
    print(transpose(m1));
    print(add(m1, transpose(m1)));

}
