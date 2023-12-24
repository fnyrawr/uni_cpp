#include<array>

// namespace my for test12.cpp class
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
                for ( int i=0; i<N; i++ )
                {
                    if ( rhs[i] != arr_[i] )
                    {
                        return false;
                    }
                }
                return true;
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
            // addition & assignment operator, assigning to lhs
            Vec<T,N>& operator+=(const Vec<T,N>& rhs)
            {
                for (int i=0; i<N; i++)
                {
                    arr_[i] += rhs[i];
                }
                return *this;
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
                for (int i=0; i<N; i++)
                {
                   temp[i] = -temp[i];
                }
                return temp;
            }

        private:
            // float std::array for values x,y,z
            std::array<T,N> arr_;
    };

    // dot product
    template <typename T, int N>
    T dot(const Vec<T,N>& lhs, const Vec<T,N>& rhs)
    {
        T r=0;
        for (int i=0; i<N; i++)
        {
            r += lhs[i]*rhs[i];
        }
        return r;
    }

}