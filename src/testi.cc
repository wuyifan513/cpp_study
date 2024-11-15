#include<stdio.h>
#include<algorithm>
#include<iostream>
using namespace std;
class Base{
public:
    Base(){};
    ~Base(){};
    virtual void f(){
        cout << "Base!" << endl;
    }
};
class Derived:public Base{
public:
    Derived(){};
    ~Derived(){};
    void f(){
        cout << "Derived!" << endl;
    }
};
class Derived1:public Base{
public:
    Derived1(){};
    ~Derived1(){};
    void f()override{
        cout << "Derived1!" << endl;
    }
};
void show(Base* A){
    A->f();
}
int main(){
    Derived* B = new Derived();
    show(B);
    show(dynamic_cast<Base*> (B));
    Base* BA = (Base*)B;
    Derived1* C = new Derived1();
    Base* CA = (Base*)C;
    BA->f();
    show(BA);
    show(B);
    printf("Hello World");
    return 0;
}