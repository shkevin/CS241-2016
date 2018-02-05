/* ************************************
 * Kevin Cox
 *
 * Reads in a file and outputs
 * the desired format, binary or
 * decimal.
 *
 ************************************ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

long unsigned binaryToDecimal(char* str, int base);
void printNum(long size);
void decimalToBinary(long num, int size);
void errorMessage();
void printfcomma(long unsigned n, int size);
char* addPaddingToDecimal(int length, int size);
unsigned numDigits(const unsigned n);

int array[64]; /*global array for binary numbers*/
int commaCount;

int main(int argc, char *argv[])
{
  /*varibales*/
  char *option, *number, *argSize;
  long unsigned num;
  long decimalNum;
  int size, errorFlag, i, tempLength;
  num = commaCount = errorFlag = tempLength = 0;

  /*pointers for argument vector*/
  option = argv[1];
  size = strtol(argv[2], &argSize, 10);
  number = argv[3];

  if (argc != 4)
  {
    printf("ERROR: incorrect number of arguments\n");
    errorMessage();
    return 1;
  }

  if(size == -8) size = 8;
  else if(size == -16) size = 16;
  else if(size == -32) size = 32;
  else if(size == -64) size = 64;
  else
  {
    printf("ERROR: argument 2 must be: -8 | -16 | -32 | -64\n");
    errorMessage();
    return 1;
  }
  /*checking for decimal to binary option*/
  if ((strcmp(option,"-d") == 0))
  {
    for (i = 0; number[i] != 0; ++i)
    {
      if (!isdigit(number[i]))
      {
        errorFlag = 1;
        break;
      }
    }
    if (errorFlag)
    {
      printf("ERROR: argument 3 is not a decimal integer\n");
      errorMessage();
      return 1;
    }
    else
    {
      decimalNum = strtol(argv[3], &number, 10);
      decimalToBinary(decimalNum, size);
      printNum(size);
      memset(array, 0, sizeof array);
    }
    
  }
  /*checking for binary to decimal option*/
  else if ((strcmp(option, "-b") == 0))
  {

    for (i = 0; number[i] != 0; ++i)
    {
      if (number[i] != '1' && number[i] != '0')
      {
        errorFlag = 1;
        break;
      }
    }
    if (errorFlag)
    {
      printf("ERROR: argument 3 is not a binary integer\n");
      errorMessage();
      errorFlag = 0;
    }
    else
    {
      /*error checking for correct number of bits*/
      tempLength = strlen(number);
      for (i = 0; i < size; ++i)
      {
        if (tempLength > size)
        {
          number[i] = '0';
          tempLength--;
        }
        else break;
      }

      num = binaryToDecimal(number, 2);
      if (num == -1)
      {
        printf("ERROR: argument 2 must be: -8 | -16 | -32 | -64\n");
        errorMessage();
        return 1;
      }
      else
      {
        printfcomma(num, size);
      }
      printf("\n");
    }
  }
  else
  {
    printf("ERROR: argument 1 must be -b | -d\n");
    errorMessage();
  }
  errorFlag = 0;
  return 0;
}

/*
 * converts provided integer to binary
 */
void decimalToBinary(long num, int size)
{
  if (num/2)
  {
    decimalToBinary(num/2, --size);
  }
  else size--;
  array[size] = num%2;
}

/*
 * prints array of numbers with correct spacing.
 */
void printNum(long size)
{
  int i;
  for (i = 0; i < size; ++i)
  {
    if (((i % 4) == 0) && i != 0 )
    {
      printf(" ");
    }
    printf("%d",array[i]);
  }
  printf("\n");
}

/*
 * converts provided string into decimal, from binary
 */
long unsigned binaryToDecimal(char* str, int base)
{
  int i;
  long unsigned decimal = 0;
  for (i=0; str[i] != 0; i++)
  {
    decimal *= base;
    decimal += str[i]-'0';
  }
  return decimal;
}

/*
 * prints comma's in correct place
 * code is a snippet from stackoverflow.com
 * by paxdiablo and modified.
 */
void printfcomma(long unsigned n, int size)
{
  int temp = numDigits(n);
  if (n < 1000)
  {
    printf("%s%lu", addPaddingToDecimal(temp+commaCount, size), n);
    return;
  }
  commaCount+=4;
  printfcomma(n/1000, size);
  printf(",%lu", n%1000);
}

void errorMessage()
{
  printf("usage:\n"
           "./binary OPTION SIZE NUMBER\n"
           "  OPTION:\n"
           "    -b    NUMBER is binary and output will be in decimal.\n"
           "    -d    NUMBER is decimal and output will be in binary.\n\n"

           "  SIZE:\n"
           "    -8    input is an unsigned 8-bit integer.\n"
           "    -16   input is an unsigned 16-bit integer.\n"
           "    -32   input is an unsigned 32-bit integer.\n"
           "    -64   input is an unsigned 64-bit integer.\n\n"

           "  NUMBER:\n"
           "    number to be converted.\n\n");
}

char* addPaddingToDecimal(int length, int size)
{
  int maxPadding, i;
  char* msgOut;

  if(size == 8) maxPadding = 3;
  else if(size == 16) maxPadding = 6;
  else if(size == 32) maxPadding = 13;
  else if(size == 64) maxPadding = 25;

  msgOut = (char *) malloc(maxPadding - length);

  for (i = 0; i < (maxPadding - length); ++i)
  {
     msgOut[i] = ' ';
  }
  return msgOut;
}

unsigned numDigits(const unsigned n) 
{
    if (n < 10) return 1;
    return 1 + numDigits(n / 10);
}
