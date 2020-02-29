#include <stdio.h>

int pop(int x) {
    if(x < 0) throw "Negative x";
    else return x;
}

int func() {
    try {
        return pop(-1);
    } catch (const char *err) {
        printf("Caught in func %s\n", ex);
        throw;
        return 0;
    }
}

int main(void) {
    try {
        int t = pop(5);
        int q = func();
    } 
    catch (const char *err) {
        printf("Caught %s\n", err);
    }
}