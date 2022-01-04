#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readEncodedFile(char* pszfileName)
{
	FILE *fHex, *fText;
	long buf;
	fHex = fopen (pszfileName, "rt");
	if (fHex != NULL) {
		fText = fopen("decoded.txt", "w");
		if (fText != NULL)
		{
			while (!feof(fHex))
			{
				char test = getc(fHex);
				char test2 = getc(fHex);
				char a[2] = {test, test2};
				char *ptr;
				buf = strtoul(a, &ptr, 16);
				fprintf(fText, "%c", (int)buf);
			}
		}
		fclose(fText);
    }
	fclose (fHex);
}
