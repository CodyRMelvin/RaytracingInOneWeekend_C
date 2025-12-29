#include <stdio.h>

#include "Vector.h"
#include "Color.h"
#include "Ray.h"

inline Vec3 Ray_Color(Ray r)
{
    Vec3 unitDirection = Vec3_UnitVector( r.dir );
    double a = .5 * unitDirection.y + 1.0;
    return Vec3_Add( Vec3_Multiply( (Vec3){ 0, 0, 0 }, 1.0 - a ), Vec3_Multiply( (Vec3){ .5, .7, 1.0 }, a ) );
}

int main(void)
{
    FILE* ppm = fopen( "image.ppm", "rw+" );
    
    //Image details
    double aspect = 16.0 / 9.0;
    int imageWidth = 400;

    int imageHeight = (int)( (double)imageWidth / aspect );
    imageHeight = imageHeight < 1 ? 1 : imageHeight;


    //Camera details
    double focalLength = 1.0;
    double viewHeight = 2.0;
    double viewWidth = viewHeight * (double)imageWidth / (double)imageHeight;
    Vec3 camCenter = (Vec3){ 0, 0, 0 };

    Vec3 viewU = (Vec3){ viewWidth, 0, 0 };
    Vec3 viewV = (Vec3){ 0, -viewHeight, 0 };

    Vec3 deltaU = Vec3_Divide( viewU, imageWidth );
    Vec3 deltaV = Vec3_Divide( viewV, imageHeight );

    Vec3 viewUpperLeft = Vec3_Subtract( camCenter, 
                         Vec3_Subtract( (Vec3){ 0, 0, focalLength }, 
                         Vec3_Subtract( 
                         Vec3_Multiply( deltaU, 0.5 ), 
                         Vec3_Multiply( deltaV, 0.5 ) 
                         ) ) );
    Vec3 pixel00 = Vec3_Add( viewUpperLeft, Vec3_Multiply( Vec3_Add( deltaU, deltaV ), 0.5 ) );

    fprintf( ppm, "P3\n%i %i\n255\n", imageWidth, imageHeight );

    for ( int j = 0; j < imageHeight; ++j )
    {
        printf( "\rScanlines remaining: %i ", imageHeight - j );
        fflush(stdout);

        for ( int i = 0; i < imageWidth; ++i )
        {
            Vec3 pixelCenter = Vec3_Add( pixel00, Vec3_Add( Vec3_Multiply( deltaU, (double)i ), Vec3_Multiply( deltaV, (double)j ) ) );
            Ray r = (Ray){ .origin = camCenter, .dir = Vec3_Subtract( camCenter, pixelCenter ) };

            Vec3 color =  Ray_Color(r);
            WriteColor( ppm, color );
        }
    }

    printf("\rDone!");
    fflush(stdout);
    
    fclose(ppm);
    return 0;
}
