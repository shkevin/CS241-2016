/* ************************************
* Kevin Cox
* hides message within a given image
************************************ */

#include <stdio.h>
#include <stdlib.h>

int getIntFromArray(unsigned char bytes[]);

int main(int argc, char *argv[])
{
  char *imageName = argv[1];
  char *fileNameToGenerate = argv[2];
  char msgToEncrypt;
  unsigned char header[54];
  int leftBitShift, increment, i, j;

  FILE* in = fopen(imageName, "rb");
  FILE* out = fopen(fileNameToGenerate, "wb");

  int pixelWidth;
  int pixelHeight;

  fread(header, 1, 54, in);

  pixelWidth = getIntFromArray(&header[18]);
  pixelHeight = getIntFromArray(&header[22]);

  /* write header to output file */
  fwrite(header, 1, sizeof(header), out);

  /*prcoess secret message here*/
  for(i = 0; i < pixelHeight; ++i)
  {
   for(j = 0; j < pixelWidth; ++j)
   {
    char temp;
    unsigned char bytes[3];
    leftBitShift = 0;
    msgToEncrypt = getchar();

    if (msgToEncrypt != EOF)
    {
      fread(bytes, 1, 4, in);
      temp = msgToEncrypt;
      /*encrypt here*/
      for (increment = 0; increment < 4; ++increment)
      {
        temp = (temp << leftBitShift) >> 6;  /*shift off everything but what is needed*/
        bytes[increment] = ((bytes[increment] >> 2) << 2) 
          | temp;                            /*shift off last two*/
        temp = msgToEncrypt;
        leftBitShift += 2;                   /*increment bitShift*/
      }
      fwrite(bytes, 1, 4, out);
    }
    else
    {
      while(fread(bytes, 1, 1, in) == 1)     /*encode null terminator*/
      {
        bytes[0] = ((bytes[0] >> 2) << 2);
        fwrite(bytes, 1, 1, out);
      }
    }
  }
}
fclose(in);
fclose(out);
return 0;
}

/**********************************************************************/
/* Take 4 bytes from an unsigned char array and assemble them into an */
/* int where the first element of the array is the least significant  */
/* byte of the int.                                                   */
/**********************************************************************/
int getIntFromArray(unsigned char bytes[])
{
  int n =
  bytes[0] |
  bytes[1] << 8 |
  bytes[2] << 16 |
  bytes[3] << 24;
  return n;
}