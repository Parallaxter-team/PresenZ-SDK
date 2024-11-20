/**
* \file
* Basic data types and scalar operations
*/

#pragma once
#include "constant.h"
#include <cmath>
#include <cstdlib> 



/**
* Return the cubic root of a float
@param[in] v cubic root of this value.
@return the cubic root.
**/
inline float nozCubeRoot(float v)
{
    if (v < 0)
        return -pow(-v, 1 / 3.0f);

    return pow(v, 1 / 3.f);
}

/**
* Rounding a float.
@param[in] in the value to convert.
@return The rounded value.
**/
template <typename T>
int nozRound(T in)
{
    int result = (int)in;
    if ((in - 1.0f*result)>0.5f)
        result++;
    return (result);
}

/**
* Linear interpolation between 'a' and 'b' using 't' (0<=t<=1)
*/
template <typename T1, typename T2>
inline T1 nozLerp(T2 t, T1 a, T1 b)
{
    return ((1 - t) * a) + (b * t);
}

/**
* Clamp the input to the specified range
*/
template <typename T>
inline T nozClamp(T v, T lo, T hi)
{
    return (v > lo) ? ((v > hi) ? hi : v) : lo;
}

/**
* Unmap a value within a range
**/
template <typename T>
inline T nozUnmap(T v, T lo, T hi)
{
    return v * (hi - lo) + lo;
}


/**
* Remap a value to a range
**/
template <typename T>
inline T nozRemap(T v, T lo, T hi)
{
    v = nozClamp(v, lo, hi);
    return (v - lo)/(hi - lo);
}

/**
* Square of 'a'
*/
template <typename T>
inline T nozSqr(T a)
{
    return (a * a);
}

/**
* Maximum of 'a' and 'b'
*/
template <typename T>
inline T nozMax(T a, T b)
{
    return (a > b) ? a : b;
}

/**
* Maximum of three values: a, b, c
*/
template <typename T>
inline T nozMax3(T a, T b, T c)
{
    return nozMax(nozMax(a, b), c);
}

/**
* Minimum of 'a' and 'b'
*/
template <typename T>
inline T nozMin(T a, T b)
{
    return (a < b) ? a : b;
}

/**
*Linear interpolation between 'a' and 'b' using 't' (0 <= t <= 1)
**/
template <typename T1, typename T2>
inline T1 NozLerp(T2 t, T1 a, T1 b)
{
    return ((1 - t) * a) + (b * t);
}


/**
* Hermite interpolation between 0 and 1 using 't' (0<=t<=1)
**/
template <typename T>
inline T nozHerp01(T t)
{
    return t * t * ((T)3 - (T)2 * t);
}
/**
* Smoothstep interpolation between 0 and 1 using 't' (0<=t<=1)
**/
template <typename T>
inline T nozSmoothstep(T e0, T e1, T t)
{
    return nozHerp01(nozClamp((t - e0) / (e1 - e0), (T)0, (T)1));
}
