/* ************************************
* Kevin Cox
* hides message within a given image
************************************ */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	char byte;								/*byte to read in*/
	int size, i, decodedMsg, bitShift;		
	FILE* myFile = fopen(argv[1], "r");		/*file read in from args*/
	decodedMsg = i = size = 0;
	fseek(myFile, 0, SEEK_END);				/*used to get size*/
	size = ftell(myFile);			
	fseek(myFile, 54, SEEK_SET);			/*skip header of the file*/
	bitShift = 6;

	for (i = 0; i < size; ++i)
	{
		byte = fgetc(myFile);
		decodedMsg = ((byte & 3) << bitShift) | (decodedMsg);
		if (bitShift <= 0)
		{
			if (decodedMsg == 00) return 0; /*if end of file*/
			printf("%c", decodedMsg);
			decodedMsg = 0;
			bitShift = 8; /*reset bitMask to 6 for new message*/
		}
		bitShift -= 2;
	}
	fclose(myFile);
	return 0;
}
