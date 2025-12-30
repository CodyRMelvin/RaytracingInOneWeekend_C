#include "Hittable.h"


typedef struct Hittable
{
    HitFunction m_hitFunction;
    void* m_dataStruct;

}Hittable;

bool Hittable_Hit( Hittable object, Ray r, double rayTMin, double rayTMax, HitRecord* record )
{
    return object.m_hitFunction( object, r, rayTMin, rayTMax, record );
}
