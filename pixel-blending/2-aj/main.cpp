
#include <stdio.h>


struct pixel_out_s
{
  unsigned int r;   // 8.24  fixed point
  unsigned int g;
  unsigned int b;
};


struct pixel_in_s
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
};


// globals
int ww, hh;   // input image w/h
size_t pixels_per_sprite = 0;


// _______________________________________________________________

int write_output_frame_to_disk( const pixel_out_s* out, const int frame_idx = 0 )
{
  char fn[64]{};
  snprintf( fn, 63, "frame%03d.ppm", frame_idx );

  FILE* fp_out = fopen( fn, "wt" );
  if ( nullptr == fp_out )
  {
    printf("\nERROR: failed to fopen for output file=%s\n", fn );
    return -2;    // failure
  }

  fprintf( fp_out, "P3\n%d %d 255\n", ww, ww );
  for ( size_t i=0 ; i < pixels_per_sprite ; i++ )
  {
    fprintf( fp_out, "%d %d %d ", ( out[i].r >> 24 ) & 0xff, ( out[i].g >> 24 ) & 0xff, ( out[i].b >> 24 ) & 0xff );
  }
  fclose( fp_out );
  fp_out = nullptr;

  return 0; // OK
}

// ____________________________________________________________

int do_it()
{
  FILE* fp_in = fopen("input.ppm", "rt" );
  if ( nullptr == fp_in )
    return 1;
  int depth;
  if ( 3 != fscanf( fp_in, "P3\n%d %d %d\n", &ww, &hh, &depth ))
    return 2;

  printf("w=[%d] h=[%d] depth=[%d]... expect 100, 19900, 255\n", ww, hh, depth );
  const size_t pixel_count = ww * hh; // 3 pixels but we are going to store in u32's
  pixel_in_s* pixels = new pixel_in_s[pixel_count];
  if ( nullptr == pixels )
    return 3;

  for ( size_t i=0 ; i < pixel_count ; i++ )
  {
    int r,g,b;
    if ( 3 != fscanf( fp_in, "%d %d %d ", &r, &g, &b )) // &pixels[i].r, &pixels[i].g, &pixels[i].b ))
      return 4+i;
    pixels[i].r = r & 0xff;
    pixels[i].g = g & 0xff;
    pixels[i].b = b & 0xff;
  }
  fclose( fp_in );
  fp_in = nullptr;

  // image is now read into  pixels[]
  // _______________________________________________________________


  const size_t sprite_count = hh / ww;
  printf("num sprites = %d\n", (int)sprite_count );

  pixels_per_sprite = ww * ww;
  printf("pixels_per_sprite = %d\n", pixels_per_sprite );

  pixel_out_s* out = new pixel_out_s[pixels_per_sprite];
  if ( nullptr == out )
  {
    printf("\nERROR: failed to alloc %d struct's of sizof(pixel_out_s)=%d\n", pixels_per_sprite, sizeof(pixel_out_s) );
    return -1;
  }

  for ( size_t s=0 ; s < sprite_count ; s++ )
  {
    const pixel_in_s* pIn = &pixels[s * pixels_per_sprite];
    pixel_out_s* pOut = out;
    for ( size_t k=0 ; k < pixels_per_sprite ; k++ )
    {
      pOut->r = ( pOut->r >> 1 ) + ( static_cast<unsigned int>( pIn->r ) << 23);  // 23 = (<<24)fixed point adjustment,  >>1 for (/0.5)
      pOut->g = ( pOut->g >> 1 ) + ( static_cast<unsigned int>( pIn->g ) << 23);
      pOut->b = ( pOut->b >> 1 ) + ( static_cast<unsigned int>( pIn->b ) << 23);
      pOut++;
      pIn++;
    }

    // write_output_frame_to_disk( out, s );

  }
  //  blending done, result  is in  out[]
  // __________________________________________________________

  if ( 0 != write_output_frame_to_disk( out, 9999999 ))
  {
    printf("\nERROR: failed to write to disk\n" );
    return -99;   // failure
  }

  return 0;
}

// ________________________________________________________________

int main(void)
{
  const int d = do_it();
  if ( 0 != d )
  {
    printf("ERROR: %d\n", d );
  }
  return d;
}

