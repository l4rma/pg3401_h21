#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getLength(char *str)
{
	int n = 0;;
	while(str[n])
	{
		n++;
	}
	return n;
}

void countLetters(char *str)
{
	int i; // Loop through string
	int j; // Inner loop through string
	int n; // Length of string
	int counter = 0; // Count letter occurences 
	n = getLength(str);

	// Tell antall forekomster av hver bokstav i teksten
	for (i = 0; i < n; i++)
	{
		str[i] = tolower(str[i]);
		counter = 1;
		if (str[i])
		{
			for (j = i + 1; j < n; j++)
			{
				str[j] = tolower(str[j]);
				if (str[i] == str[j]) 
				{
					counter++;
					str[j] = '\0';
				}
			}
			if (isalpha(str[i]))
			{
				printf("%c: %d\n", str[i], counter);
			}
		}
	}
}

void countLettersFromFile(char *filename)
{
	FILE *f = NULL;
	long lSize;
	char *buf = 0;
	f = fopen (filename, "rt"); 
	if (f != NULL) 
	{                                                             
		if (fseek(f, 0, SEEK_END) == 0) 
		{                                         
			lSize = ftell(f);                                                      
			rewind(f);                                                             
			buf = malloc(lSize + 1);                                             
			if (buf != NULL)
			{                                                
				int ok = fread(buf, 1, lSize, f);              
			}                                                                      
		}                                                                         
		buf[lSize] = '\0';
		fclose (f);                                                               
	}           
	if(buf)
	{
		// Tell og print ut resultat
		countLetters(buf);
	}
	free(buf);
}
