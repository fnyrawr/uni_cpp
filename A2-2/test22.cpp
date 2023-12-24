#include <iostream>
#include <cassert>
#include "my_vector.h"
#include "payload.h"

void test_22()
{
    using my::vector;
    using std::cout;
    using std::endl;

    {
        cout << "copy, move ... ";
        {
            vector<Payload> v0(3, Payload(-1,-1,-1));
            assert(Payload::count() == 3);

            vector<Payload> v1 (v0);
            assert(v1.capacity() == 3);
            assert(v1.size() == 3);
            assert(Payload::count() == 6);
            assert(v0.pop_back() == Payload(-1,-1,-1));
            assert(v1.pop_back() == Payload(-1,-1,-1));
            assert(v0.pop_back() == v1.pop_back());
            assert(v0.pop_back() == v1.pop_back());
            assert(Payload::count() == 0);
        }
        {
            vector<Payload> v0;
            vector<Payload> v1(3, Payload(0, 0, 0));
            assert(Payload::count() == 3);
            v0 = std::move(v1);
            assert(v0.size() == 3);
            assert(v0.capacity() == 3);
            assert(Payload::count() == 3);
        }

        cout << " done." << endl;
    }

    {
        cout << "push_back(), pop_back()  ... ";
        vector<Payload> v;
        v.push_back(Payload(0,0,0));
        assert(v.capacity() == 1);
        v.push_back(Payload(1,1,1));
        assert(v.capacity() == 2);
        v.push_back(Payload(2,2,2));
        assert(v.capacity() == 4);
        assert(Payload::count() == 3);

        assert(v.pop_back() == Payload(2,2,2));
        assert(v.size() == 2);
        assert(Payload::count() == 2);
        assert(v.pop_back() == Payload(1,1,1));
        assert(Payload::count() == 1);
        assert(v.pop_back() == Payload(0,0,0));
        assert(Payload::count() == 0);

        try {
            v.pop_back();
            assert(!"should have thrown exception");
        } catch(std::out_of_range ex) {
                cout << "exception: " << ex.what();
        }
        cout << " done." << endl;
    }

    {
        cout << "clear()  ... ";
        vector<Payload> v;
        v.push_back(Payload(0,0,0));
        v.push_back(Payload(1,1,1));
        v.push_back(Payload(2,2,2));
        v.clear();
        assert(v.size() == 0);
        assert(Payload::count() == 0);
        assert(v.capacity() == 4);
        cout << " done." << endl;
    }

    {
        cout << "reserve(), shrink_to_fit()  ... ";
        {
            vector<Payload> v;
            v.push_back(Payload(0,0,0));
            v.reserve(100);
            assert(v.at(0) == Payload(0,0,0));
            assert(v.capacity() == 100);
            assert(Payload::count() == 1);

            try {
                v.reserve(-100);
                assert(!"should have thrown exception");
            } catch(std::out_of_range ex) {
                cout << "exception: " << ex.what();
            }
        }
        {
            vector<Payload> v;
            v.reserve(100);
            v.push_back(Payload(0,0,0));
            v.push_back(Payload(1,1,1));
            v.push_back(Payload(2,2,2));
            assert(v.capacity() == 100);
            v.shrink_to_fit();
            assert(v.capacity() == 3);
        }
        cout << " done." << endl;
    }
}