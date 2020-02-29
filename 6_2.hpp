#include <iostream>
#include <time.h>

class adder {
public:
    virtual int add(int, int) = 0;
};

class add_simple : public adder {
public:
    int add(int x, int y) {
        return x + y;
    }
};

int main(int argc, char **argv) {
    const int N = argc > 1 ? atoi(argv[1]) : 10000000;
    adder *as = new add_simple();
    clock_t start = clock();
    int sum = 0;
    for(int i = 0; i < N; i++) {
        sum = as->add(sum, 1);
    }
    clock_t end = clock();
    printf("sum=%d time=%.3f\n", sum, (double) (end-start)/CLOCKS_PER_SEC);

}