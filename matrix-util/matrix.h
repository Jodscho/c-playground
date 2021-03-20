struct matrix {
    int rows;
    int cols;
    double* values;
};

extern struct matrix* create(int rows, int cols, double* vals);
extern struct matrix* createsymmetric(int rows, int cols, double* vals);
extern struct matrix* multiply(struct matrix* m1, struct matrix* m2);
extern struct matrix* transpose(struct matrix* m);
extern struct matrix* add(struct matrix* m1, struct matrix* m2);
extern struct matrix* subtract(struct matrix* m1, struct matrix* m2);
extern struct matrix* dividebyfactor(struct matrix* m1, double factor);
extern struct matrix* multiplybyfactor(struct matrix* m1, double factor);
extern struct matrix* colasmatrix(struct matrix* m1, int col);
extern struct matrix* createzeromatrix(int rows, int cols);
extern struct matrix* inverse(struct matrix* m);
extern struct matrix* identity(int rows);
extern double determinant(struct matrix* m);
extern double at(struct matrix* m, int row, int col);
extern void setat(struct matrix* m, int row, int col, double val);
extern void print(struct matrix* m);
extern void freem(struct matrix* m);
