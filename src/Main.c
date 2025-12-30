#include <stdio.h>

#include "Vector.h"
#include "Color.h"
#include "Ray.h"

extern inline double HitSphere( Vec3 center, double radius, Ray r )
{
    Vec3 OC = Vec3_Subtract( center, r.origin );
    double a = Vec3_Dot( r.dir, r.dir );
    double b = -2.0 * Vec3_Dot( r.dir, OC );
    double c = Vec3_Dot( OC, OC ) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if ( discriminant < 0 )
        return -1.0;
    else
        return ( -b - sqrt(discriminant) ) / ( 2.0 * a );
    
}

extern inline Vec3 Ray_Color(Ray r)
{
    double t = HitSphere( (Vec3){ .x = 0, .y = 0, .z = -1 }, 0.5, r );
    if ( t > 0 )
    {
        Vec3 N = Vec3_UnitVector( Vec3_Subtract( Ray_At( r, t ), (Vec3){ .x = 0, .y = 0, .z = -1 } ) );
        return Vec3_Multiply( Vec3_Add( N, (Vec3){ .x = 1, .y = 1, .z = 1 } ), .5 );
    }

    Vec3 unitDirection = Vec3_UnitVector( r.dir );
    double a = .5 * ( unitDirection.y + 1.0 );
    return Vec3_Add
    ( 
        Vec3_Multiply( (Vec3){ .x = 1, .y = 1, .z = 1 }, 1.0 - a ), 
        Vec3_Multiply( (Vec3){ .x = .5, .y = .7, .z = 1.0 }, a ) 
    );
}

int main(void)
{
    FILE* ppm = fopen( "image.ppm", "w" );
    if (!ppm)
        assert( false && "File failed to open" );
    
    //Image details
    double aspect = 16.0 / 9.0;
    int imageWidth = 400;

    int imageHeight = (int)( (double)imageWidth / aspect );
    imageHeight = imageHeight < 1 ? 1 : imageHeight;


    //Camera details
    double focalLength = 1.0;
    double viewHeight = 2.0;
    double viewWidth = viewHeight * ( (double)imageWidth / (double)imageHeight );
    Vec3 camCenter = (Vec3){ .x = 0, .y = 0, .z = 0 };

    Vec3 viewU = (Vec3){ .x = viewWidth, .y = 0, .z = 0 };
    Vec3 viewV = (Vec3){ .x = 0, .y = -viewHeight, .z = 0 };

    Vec3 deltaU = Vec3_Divide( viewU, imageWidth );
    Vec3 deltaV = Vec3_Divide( viewV, imageHeight );

    Vec3 viewUpperLeft = camCenter;
    Vec3_RefSubtract( &viewUpperLeft, (Vec3){ .x = 0, .y = 0, .z = focalLength } );
    Vec3_RefSubtract( &viewUpperLeft, Vec3_Multiply( viewU, 0.5 ) );
    Vec3_RefSubtract( &viewUpperLeft, Vec3_Multiply( viewV, 0.5 ) );
    Vec3 pixel00 = Vec3_Add( viewUpperLeft, Vec3_Multiply( Vec3_Add( deltaU, deltaV ), 0.5 ) );

    fprintf( ppm, "P3\n%i %i\n255\n", imageWidth, imageHeight );

    for ( int j = 0; j < imageHeight; ++j )
    {
        printf( "\rScanlines remaining: %i ", imageHeight - j );
        fflush(stdout);

        for ( int i = 0; i < imageWidth; ++i )
        {
            Vec3 pixelCenter = Vec3_Add( pixel00, Vec3_Add( Vec3_Multiply( deltaU, (double)i ), Vec3_Multiply( deltaV, (double)j ) ) );
            Ray r = (Ray){ .origin = camCenter, .dir = Vec3_Subtract( pixelCenter, camCenter ) };

            Vec3 color =  Ray_Color(r);
            WriteColor( ppm, color );
        }
    }

    printf("\rDone!");
    fflush(stdout);
    
    fclose(ppm);
    return 0;
}
