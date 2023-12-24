#include<array>
#include<algorithm>
#include<iterator>
#include<numeric>

// namespace my for test13.cpp class
namespace my {
    template<typename T = float,int N = 3>
    class Vec {
        public:
            // constructor
            Vec<T,N>::Vec(std::array<T,N> const& v): arr_(v) {}

            // get size of Vector
            int getSize() const { return N; }

            // operators
            // mutable Vec<T,N>[i], like setter function
            auto& operator[](int i) { return arr_[i]; };
            // const Vec<T,N>[i], like getter function
            auto operator[](int i) const { return arr_[i]; };
            // comparison equal
            bool operator==(const Vec<T,N>& rhs) const
            {
                if ( std::equal( arr_.begin(), arr_.end(), rhs.arr_.begin() ) )
                    return true;
                else
                    return false;
            };
            // comparison not-equal
            bool operator!=(const Vec<T,N>& rhs) const
            {
                Vec<T,N> temp(*this);
                return !(temp==rhs);
            };
            // equals operator, assigning rhs to lhs
            Vec<T,N>& operator=(const Vec<T,N>& rhs)
            {
                for (int i=0; i<N; i++)
                {
                   arr_[i] = rhs[i];
                }
                return *this;
            }
            // equals operator, returning rhs in new vector
            Vec<T,N> operator=(const Vec<T,N>& rhs) const
            {
                return rhs;
            }
            // addition & assignment operator, assigning to lhs
            Vec<T,N>& operator+=(const Vec<T,N>& rhs)
            {
                std::transform( arr_.begin(), arr_.end(), rhs.arr_.begin() , arr_.begin(),
                    [](T a, T b) { return a+b; } );
                return *this;    
            }
            // const addition & assignment operator, creating new vector for return
            Vec<T,N> operator+=(const Vec<T,N>& rhs) const
            {
                Vec<T,N> temp(*this);
                return temp+=rhs;
            }
            // addition operator, returning new vector
            Vec<T,N> operator+(const Vec<T,N>& rhs) const
            {
                Vec<T,N> temp(*this);
                return temp+=rhs;
            }
            // unary operator, returning new inverted vector
            Vec<T,N> operator-() const
            {
                Vec<T,N> temp(*this);
                std::transform( arr_.begin(), arr_.end(), temp.arr_.begin(),
                    [](T a) { return -a; } ); 
                return temp;
            }

            /**
             * dot product
             * written inside class despite of being a free function because of converting issues with T
             * https://web.mst.edu/~nmjxv3/articles/templates.html Approach #3 was a reference for solving the issue
             */
            friend T dot(const Vec<T,N>& lhs, const Vec<T,N>& rhs)
            {
                /**
                 * warning appears because VS Code thinks we would have a possible data loss here creating the dot product
                 * however, this should work without issues like in part 1 and 2 before, so I'll suppress the warning here
                 */
                #pragma warning(suppress: 4244)
                return std::inner_product( lhs.arr_.begin(), lhs.arr_.end(), rhs.arr_.begin(), T());
            }

            // get length of the vector
            friend double length(const Vec<T,N>& v)
            {
                double length = 0;
                std::for_each(v.arr_.begin(), v.arr_.end(),
                    [&length](T a) { return length += a*a; } );
                return sqrt(length);
            }

        private:
            // float std::array for values x,y,z
            std::array<T,N> arr_;
    };

    // helper for printing vectors
    template <typename T, int N>
    void helperfunction(const std::array<Vec<T, N>,N> a)
    {
        std::for_each(a.begin(), a.end(),
            [](Vec<T,N> v) { std::cout << "{" << v[0] << "," << v[1] << "," << v[2] << "}\tLength: " << length(v) << std::endl; } );
    }

}