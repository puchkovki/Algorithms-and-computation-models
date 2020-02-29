#include <stdio.h>

class quat {
    double r, i, j, k;
public:
    /*quat() {
        r = i = j = k = 0;
    }*/
    quat(double r = 0, double i = 0, double j = 0, double k = 0): r(r), i(i), j(j), k(k) {
        /*this->r = r;
        this->i = i;
        this->j = j;
        this->k = k;*/
    }
    ~quat() {
        printf("~quat(): ");
        print();
        printf("\n");
    }
    void print() {
        printf("(%g, %g, %g, %g)\n", r, i, j, k);
    }
};

int main(void) {
    quat a(1, 2, 3, 4), b(2, 3, 4, 5), c;
    a.print(); printf("\n");
    b.print(); printf("\n");
    c.print(); printf("\n");
}