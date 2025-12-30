#pragma once

#include "Common.h"

typedef struct Ray Ray;

typedef struct HitRecord
{
    Vec3 position;
    Vec3 normal;
    double t;
}HitRecord;

typedef struct Hittable Hittable;
typedef bool(*HitFunction)(Hittable, Ray, double, double, HitRecord*);

bool Hittable_Hit( Hittable object, Ray r, double rayTMin, double rayTMax, HitRecord* record );
