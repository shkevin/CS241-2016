#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char c;
char* buffer;
int count, i, j, decrypted = 0;
unsigned long size, va = 0;
FILE* file = NULL;

int main(int argc, char** argv)
{  
  file = fopen(argv[1], "r");

  fseek(file, 0, SEEK_END);
  size = ftell(file);           
  fseek(file, 54, SEEK_SET);

  buffer = malloc(size);
  fread(buffer, size+1, 1, file);

  /* Iterate through each char */
  for (i = 0; i < size; ++i)
  {
    count++;
    c = buffer[i];    

    if(count != 5) decrypted = (decrypted << 2) | (c & 3);

    if(count == 4)
    {
      if(decrypted == 00) return 0;
      else printf("%c", decrypted );
      decrypted = count = 0;
    }
  }
 
  free(buffer);
  fclose(file);

  return 1;
}
