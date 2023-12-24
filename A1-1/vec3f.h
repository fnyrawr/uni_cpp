#include<array>

// namespace my for test11.cpp class
namespace my {
    class Vec3f {
        public:
            // constructor
            Vec3f(float x=0, float y=0, float z=0);
            
            // operators
            float& operator[](int i);
            float operator[](int i) const;
            bool operator==(const Vec3f& rhs) const;
            bool operator!=(const Vec3f& rhs) const;
            Vec3f& operator=(const Vec3f& rhs);
            Vec3f operator=(const Vec3f& rhs) const;
            Vec3f& operator+=(const Vec3f& rhs);
            Vec3f operator+=(const Vec3f& rhs) const;
            Vec3f operator+(const Vec3f& rhs) const;
            Vec3f operator-() const;

        private:
            // float std::array for values x,y,z
            std::array<float,3> xyz_;
    };

    // dot product
    inline float dot(const Vec3f& lhs, const Vec3f& rhs) { return lhs[0]*rhs[0] + lhs[1]*rhs[1] + lhs[2]*rhs[2]; }

}