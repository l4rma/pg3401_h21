#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/decoder.h"
#include "./include/letterCounter.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: ./main <filename>\n");
		return 1;
	}
	char *filename = argv[1];
	//readEncodedFile("encoded.txt");
	
	countLettersFromFile(filename);
	return 0;
}
