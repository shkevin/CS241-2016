/* ************************************
* Kevin Cox
*
* Description above main. Used by
* redirecting integer file into this.
*
************************************ */

#include <stdio.h>

#define NELEMS(x) (sizeof(x)) / (sizeof(*x))
#define UPRANGE 4294967295
#define MAX 31

unsigned setVar(int c, unsigned var);
int concat(int x, int y);
unsigned getbits(unsigned x, int p, int n);

unsigned x, result; 
int i, c, p, n, count, commaCount, previousInt, flag;

/*
 reads in the input file, shifts as necessary.
 If the x,p, or n spots aren't compatible, it 
 returns an error 
*/
int main()
{ 
  c = x = i = p = n = result = commaCount = previousInt = 0;
  count = -1;
  
  while((c = getchar()) != EOF)
  { 
  	if (commaCount < 1)  x = setVar(c, x);
  	  
    if (c == ',')
    {
      count = - 1;	
      commaCount++;
    }    
    if ((c != ',') && (c != '\n'))
    {
      if ((commaCount == 1))  p = setVar(c, p);      
      if ((commaCount == 2))  n = setVar(c, n);
    }
  	if (c == '\n')
    {   
    	if (x == UPRANGE)  printf("Error: value out of range\n"); 
    	else if (n > p+1)  printf("Error: too many bits requested from position\n");
    	else if (p > MAX)  printf("Error: position out of range\n");
    	else if (n > MAX)  printf("Error: number of bits out of range\n");
    	else
    	{
    	  result = getbits(x, p, n);
    	  printf("getbits(x=%u, p=%d, n=%d) = %d\n", x, p, n, result);
    	}  	
    	commaCount = 0;
    	count = -1;
    	x = p = n = 0;
    }
  }	
  return 0;
}

/* concantanetes the integers as they're read*/
int concat(int x, int y) {
  int temp = y;
  x *= 10;
  y /= 10;
  return x + temp;
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
  return (x >> (p+1-n)) & ~(~0 << n);
}

/* setVar: sets the current variable being called
   and concantenates if > 9
*/
unsigned setVar(int c, unsigned var)
{
  previousInt = var;
  count++;
  if ((count >= 1) && (c != ','))  var = concat(previousInt, c - '0');
  else if ((c != ',') && (c != '\n'))  var = c -'0'; 

  if (var < previousInt) /* checks for integer overflow*/
  {
    var = UPRANGE;
  }
  return var;
}
