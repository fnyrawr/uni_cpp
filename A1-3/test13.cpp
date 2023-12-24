#include <iostream>
#include <cassert>
#include <typeinfo>
using namespace std;

#include "vec.h"
using namespace my;

void test_Vec() {

#ifndef NDEBUG
    cout << "======================" << endl;
    cout << "   Testing Vec<T,N>   " << endl;
    cout << "======================" << endl;

    {
        // using for tests
        using Vec3f = Vec<float, 3>;
        using Vec5i = Vec<int, 5>;
        using Vec7d = Vec<double, 7>;

        // do not tolerate any memory overhead
        cout << "  sizeof(Vec<float,9>) == 9*sizeof(float): ";
        assert( sizeof(Vec3f) == 3*sizeof(float) );
        cout << "passed." << endl;
        cout << "  sizeof(Vec<double,3>) == 3*sizeof(double): ";
        assert( sizeof(Vec7d) == 7*sizeof(double) );
        cout << "passed." << endl;
        cout << "  sizeof(Vec<int,5>) == 5*sizeof(int): ";
        assert( sizeof(Vec5i) == 5*sizeof(int) );
        cout << "passed." << endl;
    }

    {
        cout << "  constructor & index operator: ";
        Vec<> a({});
        assert( a[0] == 0 && a[1] == 0 && a[2] == 0 );
        Vec<float,3> b({1.25f,2.67f,3.59f});
        assert( b[0] == 1.25f && b[1] == 2.67f && b[2] == 3.59f );
        Vec<double,5> c({1.456,2.679,3.598,4.235,5.097});
        assert( c[0] == 1.456 && c[1] == 2.679 && c[2] == 3.598 && c[3] == 4.235 && c[4] == 5.097 );
        Vec<int,9> d({9,8,5,6,7,3,1,2,4});
        assert( d[0] == 9 && d[1] == 8 && d[2] == 5 && d[3] == 6 && d[4] == 7 && d[5] == 3 && d[6] == 1 && d[7] == 2 && d[8] == 4 );
        cout << "passed." << endl;
    }

    {
        cout << "  read-only access to const object: ";
        const Vec<float,3> a({1,2,3});
        // the next line will throw a compiler error if there is no proper "operator[] const"
        assert( a[1] == 2 );
        cout << "passed." << endl;
    }

    {
        cout << "  write access to a non-const object: ";
        Vec<float,3> a({1,2,3});
        a[1] = 4;
        assert( a[0] == 1 && a[1] == 4 && a[2] == 3 );
        cout << "passed." << endl;
    }

    {
        cout << "  comparison: ";        
        Vec<float,3> a({1,2,3}), b({1,2,3}), c({1,2,9}), d({4,5,6});
        assert( a == b );
        assert( a == a );
        assert( a != c );
        assert( b != d );
        assert( !(a != b) );
        cout << "passed." << endl;
    }
   
    {
        // should work out of the box when using std container (!)
        cout << "  assignment: "; 
        Vec<> a({1,2,3});
        cout << a[0] << " "; // to make sure these values are not optimized away! 
        a = Vec<> ({4,5,6});
        assert( a[0] == 4 && a[1] == 5 && a[2] == 6 );
        cout << "passed." << endl;
    }
  
    {
        cout << "  addition: ";
        Vec<> a({1,2,3}), b({4,5,6});
        a += b;
        Vec<> c({5,7,9});
        assert( a == c );
        c = a + Vec<>({1,1,1});
        assert( c == Vec<>({6,8,10}) );
        Vec<> one({1,1,1}), four({4,4,4});
        one += one+one+one;
        assert( one == four);
        Vec<> x({0,0,0}), y({1,1,1}), z({2,2,2});
        x += y += z;
        assert( y == Vec<>({3,3,3}) );
        assert( x == y );
        cout << "passed." << endl;
    }
  
    {
        cout << "  unary minus: ";
        Vec<> a({1,2,3});
        assert( -a == Vec<>({-1,-2,-3}) );
        cout << "passed." << endl;
    }
   
    {
        cout << "  dot product: ";
        Vec<> a({1,2,3});
        assert(( dot(a,a) == 1*1+2*2+3*3 ));
        cout << "passed." << endl;
    }

    {
        cout << "  length: ";
        Vec<int,6> a({1,1,1,2,2,5});
        assert( length(a) == 6 );
        cout << "passed." << endl;
    }

    {
        // these tests will not compile if you forgot to declare 
        // some methods const
        cout << "  constness: ";
        const Vec<> a({1,2,3});
        assert( a[1] == 2 );
        assert( a == a );
        assert( ! (a != a) );
        assert( a+a == Vec<>({2,4,6}) );
        assert( -a == Vec<>({-1,-2,-3}) );
        assert(( dot(a,a) == 1*1+2*2+3*3 ));
        cout << "passed." << endl;
    }

    cout << "all Vec3f tests passed." << endl << endl;   

#endif // not NDEBUG

}
