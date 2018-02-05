#include <stdio.h>
#include <stdlib.h>

int extractMsg(int bitShift, int index);

int decodedMsg = 0;
FILE* myFile = NULL;
char* buffer = NULL;

int main(int argc, char** argv)
{
	char byte;
	int size = 0;
	int i = 0;
	int count = 0;
	int bitShift = 8;
	myFile = fopen(argv[1], "r");
	fseek(myFile, 0, SEEK_END);
	size = ftell(myFile);
	fseek(myFile, 54, SEEK_SET);
	buffer = malloc(size);
	fread(buffer, size+1, 1, myFile);

	for (i = 0; i < size; ++i)
  	{
    	count++;
    	byte = buffer[i];    

    	if(count != 5) decodedMsg = (decodedMsg << 2) | (byte & 3);

    	if(count == 4)
    	{
     	 	if(decodedMsg == 00) return 0;
      		else printf("%c", decodedMsg );
     		decodedMsg = count = 0;
    	}
 	 }


	fclose(myFile);
	return 0;
}

int extractMsg(int bitShift, int index)
{	
	char byte = fgetc(myFile);
	decodedMsg = ((byte & 3) << bitShift) | (decodedMsg);
	if (bitShift <= 0)
	{
		if (decodedMsg == 00) return 0;
		printf("%c", decodedMsg);
		decodedMsg = 0;
		bitShift = 8; /*reset bitMask to 6 for new message*/
	}
	index++;
	return extractMsg(bitShift-2, index);
}