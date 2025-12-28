#include <stdio.h>

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
            double r = (double)i / ( imageWidth - 1 );
            double g = (double)j / ( imageHeight - 1 );
            double b = 0.0;

            int ir = (int)( 255.999 * r );
            int ig = (int)( 255.999 * g );
            int ib = (int)( 255.999 * b );

            fprintf( ppm, " %i %i %i\n", ir, ig, ib );
        }
    }
    
    fclose(ppm);
    return 0;
}
