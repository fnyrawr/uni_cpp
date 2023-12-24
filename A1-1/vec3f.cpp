#include "vec3f.h"

using namespace my;

// constructor
Vec3f::Vec3f(float x, float y, float z)
    : xyz_() {xyz_[0] = x; xyz_[1] = y; xyz_[2] = z;}

// mutable Vec3f[i], like setter function
float& Vec3f::operator[](int i)
{
    return xyz_[i];
}

// const (read only) Vec3f[i], like getter function
float Vec3f::operator[](int i) const
{
    return xyz_[i];
}

// comparison equal, const (not mutating)
bool Vec3f::operator==(const Vec3f& rhs) const
{
    if ((xyz_[0] == rhs.xyz_[0]) && (xyz_[1] == rhs.xyz_[1]) && (xyz_[2] == rhs.xyz_[2]))
        return true;
    else
        return false;
}

// comparison not equal, const (not mutating)
bool Vec3f::operator!=(const Vec3f& rhs) const
{
    Vec3f temp(*this);
    if (temp==rhs)
        return false;
    else
        return true;
}

// equals operator, assigning rhs to lhs
Vec3f& Vec3f::operator=(const Vec3f& rhs)
{
    xyz_[0] = rhs.xyz_[0];
    xyz_[1] = rhs.xyz_[1];
    xyz_[2] = rhs.xyz_[2];
    return *this;
}

// equals operator, returning rhs in new vector
Vec3f Vec3f::operator=(const Vec3f& rhs) const
{
    return rhs;
}

// addition & assignment operator, assigning to lhs
Vec3f& Vec3f::operator+=(const Vec3f& rhs)
{
    xyz_[0] += rhs.xyz_[0];
    xyz_[1] += rhs.xyz_[1];
    xyz_[2] += rhs.xyz_[2];
    return *this;
}

// const addition & assignment operator, creating new vector for return
Vec3f Vec3f::operator+=(const Vec3f& rhs) const
{
    Vec3f temp(*this);
    return temp+=rhs;
}

// addition operator, returning new vector
Vec3f Vec3f::operator+(const Vec3f& rhs) const
{
    Vec3f temp(*this);
    return temp+=rhs;
}

// unary operator, returning new inverted vector
Vec3f Vec3f::operator-() const
{
    return Vec3f(-xyz_[0], -xyz_[1], -xyz_[2]);
}