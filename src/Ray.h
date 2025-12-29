#pragma once

#include "Vector.h"

typedef struct Ray
{
    Vec3 origin, dir;
}Ray;

[[nodiscard]] inline Vec3 Ray_At( Ray r, double t )
{
    return Vec3_Add( r.origin, Vec3_Multiply( r.dir, t ) );
}
