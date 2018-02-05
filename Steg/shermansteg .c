/************************************************************************/
/*Sherman James                                                         */
/*November 19, 2016                                                     */
/*CS-241 Section # 2                                                    */
/*Lab #8                                                                */
/*                                                                      */
/*v1.9.9                                                                */
/*                                                                      */
/*This program hides a message in a picture using Steganography         */
/************************************************************************/

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Vars */
int pos = 54;
int mask, c, i = 0;
char* buffer;
unsigned long size = 0;
FILE* file = NULL;
FILE* fileOut = NULL;

/* Prototypes */
int power(int a, int b);

/* Getting this party started! */
int main(int argc, char** argv)
{
  /*Open file for reading*/
  file = fopen(argv[1], "r");       

  /*Seek in order to get correct file size*/
  fseek(file, 0, SEEK_END);     

  /*This is the size in bytes*/       
  size = ftell(file);    

  /*Reset pointer to skip bmp image header*/           
  fseek(file, 0, SEEK_SET);        

  /*Create buffer and add file contents to memory stream*/
  buffer = malloc(size);  
  fread(buffer, size+1, 1, file);  

  /* Iterate through each char in secret message*/
  while((c = getchar()) != EOF)
  { 
    /* Modify last 2 bits of next 4 bytes with 2 bits each from this 8bit char*/   
    for(i=4; i>0; i--)
    {
      /* Get first 2 bits of char, then next 2, then next 2, then last 2 */
      mask = power(2,i*2-1) + power(2,i*2-2);
      mask = (c & mask) >> i*2-2;

      /* Clear last 2 bits from the byte at this pos */
      buffer[pos] >>= 2;
      buffer[pos] <<= 2;

      /* Insert 2 bits from char in last 2 bits slot in the byte at this pos */
      buffer[pos] = buffer[pos] | mask;

      pos++;
    }     
  }

  /* When done, write 0's to last 2 bits of 4 bytes after message for NULL */
  for(i=3; i>=0; i--)
  {
    buffer[pos] >>= 2;
    buffer[pos] <<= 2;
    pos++;
  }

  /* Write encrypted file */
  fileOut = fopen( argv[2] , "w" );
  fwrite(buffer , 1 , size , fileOut );

  return 1;
}

/* Raise first int to the power of second int - eg - power(2,3) = 2*2*2 = 8 */
int power(int a, int b)
{
  int i;
  int val = 1;
  for(i = 0; i < b; i++)
    val *= a;
  return val;
}