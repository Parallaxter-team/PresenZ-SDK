#ifndef _vector_h_
#define _vector_h_
/**
* \file
* Vector math types, operators and utilities
*/
#include "constant.h"
#include "types.h"

#include <math.h>

/** \defgroup NOZ_vector Vector API
* \brief
* This module contains vector math types and vector utilities. There
* are two equivalent definitions of the basic 3D vector type (\c NozPoint,
* and \c NozVector).
*
* \{
*/

/**
* 3D point (single precision)
*/
struct NozPoint
{
/// x	
    float x;
/// y	
    float y;
/// z	
	float z;
/// constructor	
    NozPoint(): x(0.0f),y(0.0f),z(0.0f){}
/// constructor	
    NozPoint(const NozPoint &p) : x(p.x), y(p.y), z(p.z){}
/// constructor	
    NozPoint(float ix,float iy, float iz): x(ix),y(iy),z(iz){}
/// constructor
    NozPoint(float w) : x(w), y(w), z(w) {}

/// add operator
    NozPoint operator+(const NozPoint& p) const
    {
        NozPoint temp;
        temp.x = x + p.x;
        temp.y = y + p.y;
        temp.z = z + p.z;
        return temp;
    }
/// add operator
    NozPoint& operator+=(const NozPoint& p)
    {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }
/// add operator
    NozPoint operator+(float f) const
    {
        NozPoint temp;
        temp.x = x + f;
        temp.y = y + f;
        temp.z = z + f;
        return temp;
    }
/// add operator
    NozPoint& operator+=(float f)
    {
        x += f;
        y += f;
        z += f;
        return *this;
    }
/// minus operator
    NozPoint operator-(const NozPoint& p) const
    {
        NozPoint temp;
        temp.x = x - p.x;
        temp.y = y - p.y;
        temp.z = z - p.z;
        return temp;
    }
/// minus operator
    NozPoint& operator-=(const NozPoint& p)
    {
        x -= p.x;
        y -= p.y;
        z -= p.z;
        return *this;
    }
/// minus operator
    NozPoint operator-(float f) const
    {
        NozPoint temp;
        temp.x = x - f;
        temp.y = y - f;
        temp.z = z - f;
        return temp;
    }
/// minus operator
    NozPoint& operator-=(float f)
    {
        x -= f;
        y -= f;
        z -= f;
        return *this;
    }
/// minus operator
    NozPoint operator-() const
    {
        NozPoint temp;
        temp.x = -x;
        temp.y = -y;
        temp.z = -z;
        return temp;
    }
/// multiply operator
    NozPoint operator*(const NozPoint& p) const
    {
        NozPoint temp;
        temp.x = x * p.x;
        temp.y = y * p.y;
        temp.z = z * p.z;
        return temp;
    }
/// multiply operator
    NozPoint operator*=(const NozPoint& p)
    {
        x *= p.x;
        y *= p.y;
        z *= p.z;
        return *this;
    }
/// multiply operator
    NozPoint operator*(float f) const
    {
        NozPoint temp;
        temp.x = x * f;
        temp.y = y * f;
        temp.z = z * f;
        return temp;
    }
/// multiply operator
    NozPoint operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }
/// divide operator
    NozPoint operator/(const NozPoint& p) const
    {
        NozPoint temp;
        temp.x = x / p.x;
        temp.y = y / p.y;
        temp.z = z / p.z;
        return temp;
    }
/// divide operator
    NozPoint operator/=(const NozPoint& p)
    {
        x /= p.x;
        y /= p.y;
        z /= p.z;
        return *this;
    }
/// divide operator
    NozPoint operator/(float f) const
    {
        NozPoint temp;
        float inv = 1.0f / f;
        temp.x = x * inv;
        temp.y = y * inv;
        temp.z = z * inv;
        return temp;
    }
/// divide operator
    NozPoint operator/=(float f)
    {
        float inv = 1.0f / f;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }
/// @brief comparator equal
    bool operator==(const NozPoint& p) const
    {
        return (x == p.x && y == p.y && z == p.z);
    }
/// @brief comparator not equal
    bool operator!=(const NozPoint& p) const
    {
        return !(*this == p);
    }
/// @brief copy operator
    NozPoint& operator=(float f)
    {
        x = f;
        y = f;
        z = f;
        return *this;
    }
/// @brief copy operator
    float& operator[](unsigned int i)
    {
        return *(&x + i);  // no bounds checking!
    }
/// @brief copy operator
    const float& operator[](unsigned int i) const
    {
        return *(&x + i);  // no bounds checking!
    }

    friend NozPoint operator*(float f, const NozPoint& p);
    friend NozPoint operator+(float f, const NozPoint& p);
    friend NozPoint operator-(float f, const NozPoint& p);

};
/// @brief multiply operator
inline NozPoint operator*(float f, const NozPoint& p)
{
    return p * f;
}
/// @brief add operator
inline NozPoint operator+(float f, const NozPoint& p)
{
    return p + f;
}
/// @brief minus operator
inline NozPoint operator-(float f, const NozPoint& p)
{
    NozPoint temp;
    temp.x = f - p.x;
    temp.y = f - p.y;
    temp.z = f - p.z;
    return temp;
}

/**
* 2D point
*/
struct NozPoint2
{
/// x	
    float x;
/// y	
	float y;
/// add operator
    NozPoint2 operator+(const NozPoint2& p) const
    {
        NozPoint2 temp;
        temp.x = x + p.x;
        temp.y = y + p.y;
        return temp;
    }
/// add operator
    NozPoint2& operator+=(const NozPoint2& p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }
/// add operator
    NozPoint2 operator+(float f) const
    {
        NozPoint2 temp;
        temp.x = x + f;
        temp.y = y + f;
        return temp;
    }
/// add operator
    NozPoint2& operator+=(float f)
    {
        x += f;
        y += f;
        return *this;
    }
/// minus operator
    NozPoint2 operator-(const NozPoint2& p) const
    {
        NozPoint2 temp;
        temp.x = x - p.x;
        temp.y = y - p.y;
        return temp;
    }
/// minus operator
    NozPoint2& operator-=(const NozPoint2& p)
    {
        x -= p.x;
        y -= p.y;
        return *this;
    }
/// minus operator
    NozPoint2 operator-(float f) const
    {
        NozPoint2 temp;
        temp.x = x - f;
        temp.y = y - f;
        return temp;
    }
/// minus operator
    NozPoint2& operator-=(float f)
    {
        x -= f;
        y -= f;
        return *this;
    }
/// minus operator
    NozPoint2 operator-() const
    {
        NozPoint2 temp;
        temp.x = -x;
        temp.y = -y;
        return temp;
    }
/// multiply operator
    NozPoint2 operator*(const NozPoint2& p) const
    {
        NozPoint2 temp;
        temp.x = x * p.x;
        temp.y = y * p.y;
        return temp;
    }
/// multiply operator
    NozPoint2 operator*=(const NozPoint2& p)
    {
        x *= p.x;
        y *= p.y;
        return *this;
    }
/// multiply operator
    NozPoint2 operator*(float f) const
    {
        NozPoint2 temp;
        temp.x = x * f;
        temp.y = y * f;
        return temp;
    }
/// multiply operator
    NozPoint2 operator*=(float f)
    {
        x *= f;
        y *= f;
        return *this;
    }
/// divide operator
    NozPoint2 operator/(const NozPoint2& p) const
    {
        NozPoint2 temp;
        temp.x = x / p.x;
        temp.y = y / p.y;
        return temp;
    }
/// divide operator
    NozPoint2 operator/=(const NozPoint2& p)
    {
        x /= p.x;
        y /= p.y;
        return *this;
    }
/// divide operator
    NozPoint2 operator/(float f) const
    {
        NozPoint2 temp;
        float inv = 1.0f / f;
        temp.x = x * inv;
        temp.y = y * inv;
        return temp;
    }
/// divide operator
    NozPoint2 operator/=(float f)
    {
        float inv = 1.0f / f;
        x *= inv;
        y *= inv;
        return *this;
    }
/// comparaison operator
    bool operator==(const NozPoint2& p) const
    {
        return (x == p.x && y == p.y);
    }
/// comparaison operator
    bool operator!=(const NozPoint2& p) const
    {
        return !(*this == p);
    }
/// copy operator
    NozPoint2& operator=(float f)
    {
        x = f;
        y = f;
        return *this;
    }
/// copy operator
    float& operator[](unsigned int i)
    {
        return *(&x + i);  // no bounds checking!
    }
/// copy operator
    const float& operator[](unsigned int i) const
    {
        return *(&x + i);  // no bounds checking!
    }

    friend NozPoint2 operator*(float f, const NozPoint2& p);
    friend NozPoint2 operator+(float f, const NozPoint2& p);
    friend NozPoint2 operator-(float f, const NozPoint2& p);
};
/// @brief multiply operator
inline NozPoint2 operator*(float f, const NozPoint2& p)
{
    return p * f;
}
/// @brief add operator
inline NozPoint2 operator+(float f, const NozPoint2& p)
{
    return p + f;
}
/// @brief minus operator
inline NozPoint2 operator-(float f, const NozPoint2& p)
{
    NozPoint2 temp;
    temp.x = f - p.x;
    temp.y = f - p.y;
    return temp;
}

/** \name Derived Typedefs
* \{
*/
typedef NozPoint NozVector;    /**< 3D vector (single precision) */
typedef NozPoint2 NozVector2;  /**< 2D vector */
/*\}*/

/** \name 2D Vector Operations
* \{
*/

/**
* Create a XY point from its components
*/
inline NozPoint2 nozPoint2(float x, float y)
{
    NozPoint2 out = { x, y };
    return out;
}

/**
* Create a XY vector from its components (same as NozPoint2)
*/
inline NozVector2 nozVector2(float x, float y)
{
    NozVector2 out = { x, y };
    return out;
}

/**
* Dot product:   <v1, v2>
*/
inline float NozVecDot(const NozVector2& v1, const NozVector2& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

/**
* Vector Length:   ||v1||
*/
inline float NozVecLength(const NozVector2& v1)
{
    return sqrtf(v1.x * v1.x + v1.y * v1.y);
}

/**
* Distance between two points:   ||p1-p2||
*/
inline float NozVecDist(const NozPoint2& p1, const NozPoint2& p2)
{
    return sqrtf(((p1.x - p2.x) *(p1.x - p2.x)) + ((p1.y - p2.y)*(p1.y - p2.y)));
}


/**
* Distance in double between two points:   ||p1-p2||
*/
inline double NozVecDist_d(const NozPoint2& p1, const NozPoint2& p2)
{
    double p1x = (double)p1.x;
    double p1y = (double)p1.y;
    double p2x = (double)p2.x;
    double p2y = (double)p2.y;

    return sqrt(((p1x - p2x) *(p1x - p2x)) + ((p1y - p2y)*(p1y - p2y)));
}

/**
* 3D vector linear interpolation
* (t=0 -> result=lo, t=1 -> result=hi)
*/
inline NozVector NozVecLerp(float t ,NozVector &a, NozVector &b)
{
    return ((1.0 - t) * a) + (b * t);
}

/*\}*/

/** \name 3D Vector Operations
* \{
*/

/**
* Create a XYZ point from its components
*/
inline NozPoint nozPoint(float x, float y, float z)
{
    return NozPoint(x,y,z);
}

/**
* Create a XYZ vector from its components (same as NozPoint)
*/
inline NozVector nozVector(float x, float y, float z)
{
    return NozVector(x,y,z);
}

/**
* Vector Length:   ||a||
*/
inline float NozVecLength(const NozVector& a)
{
    return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z);
}
/**
* Vector Length:   ||a||
*/
inline double NozVecLength_d(const NozVector& a)
{
    double x = (double)a.x;
    double y = (double)a.y;
    double z = (double)a.z;
    return sqrt(x*x + y*y + z*z);

}

/**
* Dot product:   <a, b>
*/
inline float NozVecDot(const NozVector& a, const NozVector& b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
/**
* Dot product:   <a, b>
*/
inline double NozVecDot_d(const NozVector& a, const NozVector& b)
{
    return (double)a.x*(double)b.x + (double)a.y*(double)b.y + (double)a.z*(double)b.z;
}


/**
* Distance between two points:   ||a-b||
*/
inline float NozVecDist(const NozVector& a, const NozVector& b)
{
    return sqrtf(nozSqr(a.x - b.x) + nozSqr(a.y - b.y) + nozSqr(a.z - b.z));
}
/**
* Distance between two points:   ||a-b||
*/
inline double NozVecDist_d(const NozVector& a, const NozVector& b)
{
    double ax = (double)a.x;
    double ay = (double)a.y;
    double az = (double)a.z;

    double bx = (double)b.x;
    double by = (double)b.y;
    double bz = (double)b.z;

    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by) + (az - bz) * (az - bz));


}

/**
* Squared distance between two points:   ||a-b||^2
*/
inline float NozVecDist2(const NozVector& a, const NozVector& b)
{
    return nozSqr(a.x - b.x) + nozSqr(a.y - b.y) + nozSqr(a.z - b.z);
}

/**
* Signed distance between point x and a plane defined by point p and normalized vector n
*/
inline float NozVecDistPlane(const NozPoint& x, const NozPoint& p, const NozVector& n)
{
    return NozVecDot(x, n) - NozVecDot(p, n);
}


/**
* Cross product:   a x b
*/
inline NozVector NozVecCross(const NozVector& a, const NozVector& b)
{
    NozVector out;
    out.x = a.y * b.z - a.z * b.y;
    out.y = a.z * b.x - a.x * b.z;
    out.z = a.x * b.y - a.y * b.x;
    return out;
}

/**
* Normalize a vector:   a / ||a||
*/
inline NozVector NozVecNormalize(const NozVector& a)
{
    float tmp = NozVecLength(a);
    if (tmp != 0.0)
        tmp = 1.0 / tmp;
    NozVector out;
    out.x = a.x * tmp;
    out.y = a.y * tmp;
    out.z = a.z * tmp;
    return out;
}

/**
* Check for a zero vector, within a small tolerance
*/
inline bool NozVecIsSmall(const NozVector& a, float epsilon = NOZ_EPSILON)
{
    return fabs(a.x) < epsilon && fabs(a.y) < epsilon && fabs(a.z) < epsilon;
}

/**
* Linear interpolate two vectors.  
*/
inline NozVector NozVecLerp(const NozVector &va, const NozVector &vb, double alpha)
{
    return alpha * vb + (1 - alpha) * va;
}

//A normal is invalid if its values are infinite or extremely small
inline bool IsNormalInvalid(const NozPoint& normal)
{
    if (!std::isfinite(normal.x) || !std::isfinite(normal.y) || !std::isfinite(normal.z))
        return true;

    if (fabsf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z) < (NOZ_EPSILON*NOZ_EPSILON))
        return true;

    return false;
}


/*\}*/


/// @brief null 3D vector
#define NOZ_V3_ZERO  NozVector(0.0, 0.0, 0.0);
/// @brief 3D vector {1.0,1.0,1.0}
#define NOZ_V3_ONE  NozVector(1.0, 1.0, 1.0);


/*\}*/
#endif