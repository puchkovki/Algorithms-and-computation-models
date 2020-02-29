#include <stdio.h>

//ссылка передается внутренне как указатель на объект

class figure {
public:
    double x, y;
    virtual double getArea() = 0;
    virtual void draw() = 0;
    figure(double x = 0, double y = 0): x(x), y(y) {
        printf("figure(%g, %g)\n", x, y);
    }
    virtual ~figure() {
        printf("~figure()\n");
    }
};

class circle: public figure {
    double r;
public:
    circle(double x = 0, double y = 0, double r = 0): figure(x, y), r(r) {
        printf("circle(%g, %g, %g)\n", x, y, r)
    };
    ~circle() {
        printf("~circle()\n");
    };
    double getArea() {
        return 3.1415*r*r;
    };
    void draw() {
        printf("circle::draw()\n");
    };
};

void func(figure **f, int n) {
    for(int i = 0; i < n; i++) {
        cout << "Area[" << i << "] = " << f[i]->getArea()<< endl;
        f[i]->draw;
    }
}

int main(void) {
    figure *arra[3];
    arr[0] = new circle(1, 2, 3);
    arr[1] = new circle(4, 3, 2);
    arr[2] = new circle(0, 0, 5);
    func(arr, 3);
    delete arr[0];
    delete arr[1];
    delete arr[2];
    return 0;
}