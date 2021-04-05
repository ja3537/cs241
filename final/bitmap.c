/*******************************************************************************
 * Joseph Adams
 *
 * bitmap.c is a source file that defines the function bitmap(), along with
 * some helper functions. bitmap() is designed to take an unsigned char
 * string containing the Thue-Morse sequence, and use it to generate a Koch
 * snowflake in a .bmp file named snow.bmp.
 *
 * More comments have been added in the function bitmap() about added local
 * variables and also in the part of bitmap() where setRGB is called to print
 * the snowflake.
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



/****************************************************************************/
/* This function copies 4 bytes from an int to an unsigned char array where */
/*   the least significant byte of the int is placed in the first element   */
/*   of the array.                                                          */
/****************************************************************************/
void copyIntToAddress(int n, unsigned char bytes[])
{
  bytes[0] = n & 0xFF;
  bytes[1] = (n >>  8) & 0xFF;
  bytes[2] = (n >> 16) & 0xFF;
  bytes[3] = (n >> 24) & 0xFF;
}


/*****************************************************************************/
/* Sets the RGB value of a single pixel at coordinates (x,y) in the          */
/*    character array, data in bitmap format with three bytes per pixel.     */
/*                                                                           */
/* Bitmap format stores rows from bottom to top. Therefore, this function    */
/*    needs the pixelHeight to calculate the offset into data.               */
/*                                                                           */
/* Bitmap format requires that each row is divisible by 4. Therefore,        */
/*    rowSize may need to be padded up to 3 bytes past the end of the data.  */
/*****************************************************************************/
void setRGB(unsigned char data[], int x, int y, int rowSize,
            int pixelHeight,
            unsigned char r, unsigned char g, unsigned char b)
{
  int offset;
  y = (pixelHeight - y) - 1;
  offset = (x * 3) + (y * rowSize);
  data[offset] = b;
  data[offset+1] = g;
  data[offset+2] = r;
}

/********************************************************************************/
/* The function bitmap takes as a parameter the array containing the Thue Morse */
/* sequence that you created. Make sure to add a call to this function to your  */
/* main function when you are ready to draw the Koch snowflake                  */
/********************************************************************************/

void bitmap(unsigned char tm[])
{
      unsigned char header[54] =
        {
          'B','M',   /* magic number */
          0,0,0,0,   /* size in bytes (set below) */
          0,0,0,0,   /* reserved */
          54,0,0,0,  /* offset to start of pixel data */
          40,0,0,0,  /* info hd size */
          0,0,0,0,   /* image width (set below) */
          0,0,0,0,   /* image height (set below) */
          1,0,       /* number color planes */
          24,0,      /* bits per pixel */
          0,0,0,0,   /* compression is none */
          0,0,0,0,   /* image bits size */
          0x13,0x0B,0,0,  /* horz resolution in pixel / m */
          0x13,0x0B,0,0,  /* vert resolutions (0x03C3 = 96 dpi, 0x0B13 = 72 dpi) */
          0,0,0,0,   /* #colors in pallette */
          0,0,0,0,   /* #important colors */
        };

      int pixelWidth = 1000;
      int pixelHeight = 2400;
      int rowSize = pixelWidth * 3;
      int rowPadding;
      int pixelDataSize;
      int fileSize;
      unsigned char* img;
      FILE* myFile;
      int i;

      int xpix,ypix;
      /*
      xdir and ydir are arrays indicating the direction we will move if a
      '0' is encountered. encountering a '1' will iterate dir, which is
      used as the index for xdir and ydir.
      */
      int xdir[6] = {6,3,-3,-6,-3,3};
      int ydir[6] = {0,3,3,0,-3,-3};
      int dir = 0;

      rowPadding = (4 - (rowSize % 4)) % 4;
      rowSize += rowPadding;
      pixelDataSize = rowSize*pixelHeight;
      fileSize = 54 + pixelDataSize;

      printf("rowPadding=%d bytes\n", rowPadding);
      printf("rowSize   =%d bytes\n", rowSize);

      copyIntToAddress(fileSize, &header[2]);
      copyIntToAddress(pixelWidth, &header[18]);
      copyIntToAddress(pixelHeight, &header[22]);
      copyIntToAddress(pixelDataSize, &header[34]);

      img = malloc(pixelDataSize);

      /* Initialize all pixels to white. This also sets any row padding */
      /* to 0FF, but that data is ignored by readers. */
      memset(img,0xFF,pixelDataSize);

      /* the first pixel is drawn for you */

      xpix = 200;
      ypix = 1200;
      setRGB(img, xpix, ypix, rowSize, pixelHeight, 255, 0, 0);
      setRGB(img, xpix, ypix+1, rowSize, pixelHeight, 255, 0, 0);

      /*
      Here we have the for loop that creates our snowflake. xpix and ypix 
      represent the next pixel to be colored. In the condition where a
      '0' is encountered, we move in the direction dictated by xdir and
      ydir by adding their corresponding elements to xpix and ypix. The
      rest underneath is just printing out all the pixels of the large
      honeycomb example.

      In the event that a '1' is encountered, dir is iterated mod 6
      which has the effect of rotating clockwise by roughly 60 degrees.
       */
      for(i = 0; i < strlen((char*)tm); i++)
        {
          if(tm[i] == '0')
            {
              xpix += xdir[dir];
              ypix += ydir[dir];
              setRGB(img, xpix, ypix, rowSize, pixelHeight, 255, 0, 0);
              setRGB(img, xpix + 1, ypix, rowSize, pixelHeight, 255, 0, 0);
              setRGB(img, xpix + 2, ypix, rowSize, pixelHeight, 255, 0, 0);
              setRGB(img, xpix + 3, ypix, rowSize, pixelHeight, 255, 0, 0);
              setRGB(img, xpix + 1, ypix + 1, rowSize, pixelHeight, 255, 0, 0);
              setRGB(img, xpix + 2, ypix + 1, rowSize, pixelHeight, 255, 0, 0);
              setRGB(img, xpix + 1, ypix - 1, rowSize, pixelHeight, 255, 0, 0);
              setRGB(img, xpix + 2, ypix - 1, rowSize, pixelHeight, 255, 0, 0);

            }
          if(tm[i] == '1')
            {
              dir = (dir + 1)%6;
            }
        }
      
      
      
          
      

      myFile = fopen("snow.bmp", "wb");
      fwrite(header, 1, sizeof(header), myFile);
      fwrite(img, 1, pixelDataSize, myFile);
      fclose(myFile);

      if (0)
        { int i;
          for (i=0; i<54; i++)
            {
              printf("header[%2d]=%0X\n", i, header[i]);
            }
        }

      free(img);

}
