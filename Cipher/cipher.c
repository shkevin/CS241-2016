/* ************************************
* Kevin Cox
*
* Reads in file one bit at a time,
* encrypts or decrypts that bit as 
* specified by the file read in.
************************************ */

#include <stdio.h>
#include "lcg.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define IN 1
#define OUT 0
#define ERROR -1
#define NEWPROBLEM 2
#define DEBUG 0

void encrypt(char b);
void decrypt(char c);
int determineCipher(char c, int mode);
void skipLine();
unsigned long readToDelimeter(unsigned long num);
int printableAscii(char c);
void specialCharacters(char previous, char current);
unsigned long concat(unsigned long x, int y);
int numberCheck();

enum cipher{ENCRYPT, DECRYPT}; /*enum to toggle ciphermode*/
enum cipher ciphermode; /*value to determine encryption or decryption*/
int commaCount, mode, decimalCount; /*counts commas, program mode, num decimals*/
struct LinearCongruentialGenerator MyStruct; /*struct used to store lcg*/
struct LinearCongruentialGenerator *lcgPtr; /*pointer to access fields*/
unsigned long lcg_m, lcg_c, lcg_x; /*modulus m, increment c, seed x*/

int main()
{	
	int c, lineNumber;
	c = mode = commaCount = decimalCount = 0;
	lcg_m = lcg_c  = lcg_x = 0;
	lineNumber = 1;

	printf("%d) ", lineNumber);

	while((c = getchar()) != EOF)
	{
		mode = determineCipher(c, mode);
		if (mode == ERROR)
		{	
			skipLine();
			printf("Error");
			mode = NEWPROBLEM;
		}

		if (mode == NEWPROBLEM)
		{
			commaCount = lcg_m = lcg_c  = lcg_x = 0;
			lineNumber++;
			decimalCount = 0;
			printf("\n%d) ", lineNumber);
			continue;
		}
		else if (mode == OUT && commaCount < 2) continue;
		else
		{
			if (mode == IN && commaCount < 2)
			{
	
				lcg_m = readToDelimeter(lcg_m);
				lcg_c = readToDelimeter(lcg_c);


				if(DEBUG) printf(" before struct lcg M: %lu lcg C: %lu \n", 
					lcg_m, lcg_c);

				if(!numberCheck()) continue;
				MyStruct = makeLCG(lcg_m, lcg_c);
				lcgPtr = &MyStruct;
				if ((lcgPtr->m) == 0)
				{
					mode = ERROR;
					continue;
				}
			}
			else if(commaCount == 2)	
			{
				if (ciphermode == ENCRYPT) encrypt(c);
				else if (ciphermode == DECRYPT) decrypt(c);
			}
			else mode = ERROR;
		}
	}
	return 0;
}




/***************************************************************/
/* Helper fucntion to read in each line and determine validity */
/* Parameters: character of file read in 					   */
/* returns: if valid line 									   */
/***************************************************************/
int determineCipher(char c, int mode)
{	
	if (c == '\n') return NEWPROBLEM;

	else if (c == ',')
	{
		if(commaCount == 0) return mode = ERROR;
		return mode = OUT;
	}

	if (commaCount == 0)
	{
		if ((c == 'e'))
		{
			ciphermode = ENCRYPT;
			return IN;
		}
		else if ((c == 'd'))
		{
			ciphermode = DECRYPT;
			return IN;
		}
		else mode = ERROR;
	}
	else if (mode == ERROR) return ERROR;
	else if (commaCount == 2) return IN;
	return ERROR;
}

/***************************************************************/
/* Function to read until each comma, used before E, or D      */
/* Parameters: lcg M, or lcg C 				 				   */
/* returns: integer value for modulus M or increment C 		   */
/***************************************************************/
unsigned long readToDelimeter(unsigned long num)
{	
	char c = getchar();
	if ((isalpha(c)) || (c == ','))
	{
		if (isalpha(c)) return 0;
		commaCount++;
		return num;
	}
	num = concat(num, c - '0');
	decimalCount++;
	return readToDelimeter(num);
}

/***************************************************************/
/* Function: encrypts data as it's read in 					   */
/* Parameters: current character to be encrypted 			   */
/* returns: nothing 										   */
/***************************************************************/
void encrypt(char b)
{	
	unsigned long encryptedByte = 0;
	lcg_x = getNextRandomValue(lcgPtr);
	encryptedByte = b ^ (lcg_x % 128);
	if(printableAscii(encryptedByte));
	else mode = ERROR;
}

/***************************************************************/
/* Function: */
/* Parameters: */
/* returns: */
/*                        									   */
/***************************************************************/
void decrypt(char c)
{
	if((c < 32) || (c > 127)) mode = ERROR;
	else if(c >= 32 && c <= 126)
	{
		
	}
	else
	{
		char previous = c;
		c = getchar();
		if (c != '\n' && c != EOF)
		{
			specialCharacters(previous, c);
		}
	}
}

/***************************************************************/
/* helper function used to skip to end of line if error 	   */
/* Parameters: none											   */
/* returns: none 											   */
/***************************************************************/
void skipLine()
{	
	char c;
	while(c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

/***************************************************************/
/* helper function used check if c is within range of Ascii    */
/* Parameters: current read in character					   */
/* returns: true or false depending on validity of c 		   */
/***************************************************************/
int printableAscii(char c)
{
	if (c  < 32) printf("*%c", '@'+c);
	else if (c == 127) printf("*&");
	else if (c == '*') printf("**");
	else if (c > 126 || c < 0) return 0;
	else printf("%c", c);
	return 1;
}

/***************************************************************/
/* Function: */
/* Parameters: */
/* returns: */
/*                        									   */
/***************************************************************/
void specialCharacters(char previous, char current)
{
	if (previous == '*')
	{
		if (current == '&')
		{
			/* code */
		}
		else if (current == '*')
		{
			/* code */
		}
		else mode = ERROR;
	}
	else
	{
		mode = ERROR;
	}
}


/***************************************************************/
/* Function: concatenates numbers as it's read in 			   */
/* Parameters: previous Unsigned long, current integer 		   */
/* returns: value of x and y concatenated 					   */
/***************************************************************/
unsigned long concat(unsigned long x, int y)
{
	int temp = y;
	x *= 10;
	y /= 10;
	return x + temp;
}

int numberCheck()
{
	if(lcg_m == 0 || decimalCount > 20 || lcg_c == 0)
	{
		mode = ERROR;
		return 0;
	}
	else
	{
		return 1;
	}
}
