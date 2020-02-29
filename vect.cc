#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

class vect {
    int N;
    int *body;
    mutable int printed;
public:
    vect() { //конструктор
        printed = 0;
        N = 0;
        body = nullptr;
        for(int i = 0; i < N; i++) {
            body[i] = 0;
        }
        printf("vect()=");
        print();
        printf("\n");
    }
    vect(const int *init, int size, int printed) { //перегруженный конструктор
        printed = 0;
        N = size;
        body = new int[N];
        for(int i = 0; i < size; i++) {
            body[i] = init[i];
        }
        printf("vect(int*)=");
        print();
        printf("\n");
    }
    vect(vect const &v) { //конструктор копирования
        printed = 0;
        body = new int[N = v.N];
         for(int i = 0; i < N; i++) {
            body[i] = v.body[i];
        }
        printf("vect(vect)=");
        print();
        printf("\n");
    }
    void print() const{
        printed++;
        printf("(");
        for(int i = 0; i < N; i++) {
            printf("%d ", body[i]);
        }
        printf(")");
    }
    vect& operator=(vect const& v) { //перегруженный оператор присваивания
        N = v.N;
        delete[] body;
        body = new int[N];
         for(int i = 0; i < N; i++) {
            body[i] = v.body[i];
        }
        printf("vect:operator=");
        print();
        printf("\n");
        return *this; //this вернул указатель, разыменовали его и вернули
    }
    int operator[] (int x) const { //означает, что этот метод класса константный
        return body[x];
    }
    int& operator[] (int x) { //может быть не lvalue
        return body[x];
    }
    ~vect() {
        printf("~vect:");
        print();
        printf("printed = %d\n", printed);
        delete[] body;
    }
    int size() const{
        return N;
    }
};

int sum(vect const &v) {
    //vect _v;     _v = v;
    int res = 0;
    for(int i = 0; i < v.size(); i++) {
        res += v[i];
    }
    v.print();
    return res;
}

int main(void) {
    int t[] = {1,2,3,4,5,6,7,8,9,10};
    vect v(t, 10, 0);
    v[5] = 0;
    printf("sum of v = %d\n", sum(v));
}