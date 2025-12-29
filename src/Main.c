#include <stdio.h>

#include "Vector.h"
#include "Color.h"

int main(void)
{
    FILE* ppm = fopen( "image.ppm", "rw+" );
    
    int imageWidth = 256, imageHeight = 256;

    fprintf( ppm, "P3\n%i %i\n255\n", imageWidth, imageHeight );

    for ( int j = 0; j < imageHeight; ++j )
    {
        printf( "\rScanlines remaining: %i ", imageHeight - j );
        fflush(stdout);

        for ( int i = 0; i < imageWidth; ++i )
        {
            Vec3 color = (Vec3) 
            {
                .r = (double)i / ( imageWidth - 1 ),
                .g = (double)j / ( imageHeight - 1 ),
                .b = 0.0
            };

            WriteColor( ppm, color );
        }
    }

    printf("\rDone!");
    fflush(stdout);
    
    fclose(ppm);
    return 0;
}
