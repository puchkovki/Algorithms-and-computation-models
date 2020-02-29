#include <stdio.h>
//нельзя делать указатель на ссылку
void f(int * &a) { //ссылка на указатель (создали псевдоним для указателя) - зачем ?
    a = new int[10];
}

class mutex {
    mutex(mutex const&);
    mutex &operator=(mutex const&);
public:
    mutex() {}
    ~mutex() {}
    void lock() {}
    void unlock() {}
};

class foo {
    mutex &m;
public:
    foo(mutex &mut): m(mut) {
        m.lock();
    }
    ~foo() {
        m.unlock();
    }
};

class hashtab {
    mutex mut;
public:
    //bool hashtab() {}
    //~bool hashtab() {}
    bool insert() {
        foo f(mut);
    }
    //item find() {}
    //bool erase() {}
};


/*Для полиморфизма мы указываем в аргументах типы переменных, а не auto
Где у нас в полях классах может потребоваться ссылка? Например, для mutex
constructors can't be const-valited
засунули в private - теперь можем mutex передавать только по ссылке*/
int main(void) {
    hashtab h;
    h.insert();
    /*mutex m;
    mutex t(m);
    mutex f;
    f = m;
    int b;
    int *a = &b;
    printf("a=%p/n", a);
    f(a);
    printf("new a=%p\n", a);*/
}