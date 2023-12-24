#include "trackmymoves.h"

#include <iostream>

using namespace std;

using MyObject = TrackMyMoves;

MyObject Factory() {
    return MyObject("from factory");
}

void foo(MyObject x) {
    cout << (string)x << endl;
}

void test_copies() {
    MyObject obj1 = Factory();
    foo(MyObject("temporary0"));

    MyObject obj2("obj2");
    MyObject obj3 = MyObject("temporary1");
    obj3 = MyObject("temporary2");

}

