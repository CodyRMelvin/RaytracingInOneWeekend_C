#include "Vector.h"

void WriteColor( FILE* file, const Vec3 color )
{
    int rByte = (int)( 255.999 * color.r );
    int gByte = (int)( 255.999 * color.g );
    int bByte = (int)( 255.999 * color.b );

    fprintf( file, "%i %i %i\n", rByte, gByte, bByte );
}
