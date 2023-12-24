#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <random>
#include "vec.h"
#include "test13.h"

using namespace my;

using vec3f = Vec<float,3>;

float get_random()
{
    // source: Stackoverflow answer as given in task
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(0, 100);
    return (float)dist(e2);
}

vec3f add1(vec3f v)
{
    vec3f f({v[0] += 1, v[1] += 1, v[2] += 1});
    return f;
}

bool condition(vec3f v)
{
    return(length(v) > 120 || length(v) < 90);
}

void printVectors(const std::vector<vec3f> &v)
{
    for(auto const& i:v)
    {
        std::cout << "  { " << i[0] << ", " << i[1] << ", " << i[2] << " }\t\tLength: " << std::to_string(length(i)) << std::endl;
    }
}

int main() {
//  test_Vec();

std::cout << "\nTESTING 1.3" << std::endl;

{
    std::cout << "\n1. Testing length with ";
    vec3f a({1,2,3});
    std::cout << "  a: {" << a[0] << "," << a[1] << "," << a[2] << "}" << std::endl;
    std::cout << "  length is: " << std::to_string(length(a)) << std::endl;
    if(length(a) == sqrt(1*1+2*2+3*3)){std::cout << "  [ OK ]" << std::endl;} else {std::cout << "  [FAIL]" << std::endl;}
}    

{
    std::cout << "\n2. Print container" << std::endl;
    std::array<vec3f, 3> a{ { vec3f({1,2,3}), vec3f({4,5,6}), vec3f({7,8,9}) } };
    helperfunction(a);
}

    std::cout << "\n3. Generating 10 random vectors" << std::endl;
    std::vector<vec3f> v;
    for(int i = 0; i < 10; i++)
    {
        vec3f x({get_random(), get_random(), get_random()});
        v.push_back(x);
    }
    printVectors(v);

    std::cout << "\n4. Adding 1 to each vector" << std::endl;
    transform(v.begin(), v.end(), v.begin(), add1);
    printVectors(v);

    std::cout << "\n5. Stable Partition" << std::endl;
    stable_partition(v.begin(), v.end(), [](vec3f n){return length(n) < 90;});
    printVectors(v);

    std::cout << "\n6. Sorting container" << std::endl;
    std::sort(v.begin(), v.end(), [](vec3f a, vec3f b){return length(a) < length(b);});
    printVectors(v);

    std::cout << "\n7. Median" << std::endl;
    double median = ( length(v[4])+length(v[5]) ) / 2;
    std::cout << "  Median: " << median << std::endl;

    std::cout << "\n8. Copy if" << std::endl;
    std::vector<vec3f> v8;
    std::copy_if(v.begin(), v.end(), back_inserter(v8), [](vec3f n){return length(n) < 80;});
    printVectors(v8);

    std::cout << "\n9. Erase" << std::endl;
    auto to_be_erased = std::remove_if(v.begin(), v.end(), condition);
    v.erase(to_be_erased, v.end());
    printVectors(v);

    return 0;
}