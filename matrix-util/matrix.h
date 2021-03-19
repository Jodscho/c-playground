struct matrix {
    int rows;
    int cols;
    float* values;
};

extern struct matrix* create(int rows, int cols, float* vals);
extern struct matrix* multiply(struct matrix* m1, struct matrix* m2);
extern struct matrix* transpose(struct matrix* m);
extern struct matrix* add(struct matrix* m1, struct matrix* m2);
extern void print(struct matrix* m);
