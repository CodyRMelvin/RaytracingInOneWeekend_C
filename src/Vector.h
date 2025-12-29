#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdio.h>
#include <assert.h>

typedef struct Vec3
{
    union
    {
        struct { double x, y, z; };
        struct { double r, g, b; };
        double v[3];
    };
}Vec3;

[[nodiscard]] inline Vec3 Vec3_Negate(Vec3 vec)
{
    return (Vec3){ .x = -vec.x, .y = -vec.y, .z = -vec.z }; 
}

inline void Vec3_NegateEquals(Vec3* vec)
{
    vec->x *= -1;
    vec->y *= -1;
    vec->x *= -1;
}

[[nodiscard]] inline Vec3 Vec3_Inverse(Vec3 vec)
{
    return (Vec3){ .x = 1.0 / vec.x, .y = 1.0 / vec.y, .z = 1.0 / vec.z };
}

inline void Vec3_InverseEquals(Vec3* vec)
{
    vec->x = 1.0 / vec->x;
    vec->y = 1.0 / vec->y;
    vec->z = 1.0 / vec->z;
}

[[nodiscard]] extern inline Vec3 Vec3_Add( Vec3 vec1, Vec3 vec2 )
{
    return (Vec3){ .x = vec1.x + vec2.x, .y = vec1.y + vec2.y, .z = vec1.z + vec2.z };
}

extern inline void Vec3_RefAdd( Vec3* vec1, Vec3 vec2 )
{
    vec1->x += vec2.x;
    vec1->y += vec2.y;
    vec1->z += vec2.z;
}

[[nodiscard]] extern inline Vec3 Vec3_Subtract( Vec3 vec1, Vec3 vec2 )
{
    return (Vec3){ .x = vec1.x - vec2.x, .y = vec1.y - vec2.y, .z = vec1.z - vec2.z };
}

extern inline void Vec3_RefSubtract( Vec3* vec1, Vec3 vec2 )
{
    vec1->x -= vec2.x;
    vec1->y -= vec2.y;
    vec1->z -= vec2.z;
}

[[nodiscard]] extern inline Vec3 Vec3_Multiply( Vec3 vec, double s )
{
    return(Vec3){ .x = vec.x * s, .y = vec.y * s, .z = vec.z * s };
}

extern inline void Vec3_RefMultiply( Vec3* vec, double s )
{
    vec->x *= s;
    vec->y *= s;
    vec->z *= s;
}

[[nodiscard]] extern inline Vec3 Vec3_Divide( Vec3 vec, double s )
{
    return (Vec3){ .x = vec.x / s, .y = vec.y / s, .z = vec.z / s };
}

extern inline void Vec3_RefDivide( Vec3* vec, double s )
{
    vec->x /= s;
    vec->y /= s;
    vec->z /= s;
}

[[nodiscard]] extern inline double Vec3_LengthSquared(Vec3 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z + vec.z;
}

[[nodiscard]] extern inline double Vec3_Length(Vec3 vec) {
    return sqrt( Vec3_LengthSquared(vec) );
}

[[nodiscard]] extern inline Vec3 Vec3_UnitVector(Vec3 vec)
{
    return Vec3_Divide( vec, Vec3_Length(vec) );
}

extern inline void Vec3_Normalize(Vec3* vec)
{
    Vec3_RefDivide( vec, Vec3_Length(*vec) );
}

[[nodiscard]] extern inline double Vec3_Dot( Vec3 vec1, Vec3 vec2 )
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

[[nodiscard]] extern inline Vec3 Vec3_Cross( Vec3 vec1, Vec3 vec2 )
{
    return (Vec3)
    {
        .x = vec1.y * vec2.z - vec1.z * vec2.y,
        .y = vec1.z * vec2.x - vec1.x * vec2.z,
        .z = vec1.x * vec2.y - vec1.y * vec2.x
    };
}

void Vec3_ToString( Vec3 vec, unsigned int length, char string[length] )
{
    assert( length >= 31 && "String buffer is too short" );

    sprintf( string, "%#.9g %#.9g %#.9g\n", vec.x, vec.y, vec.z );
}

#endif
