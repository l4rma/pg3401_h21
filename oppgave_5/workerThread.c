#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "./include/workerThread.h"

void *getStringIntoFile(void *args) {
	((ARGS*)args)->f = fopen("whoNeedsALargeBuffer.txt", "a");
	if (((ARGS*)args)->f != NULL)
	{	
		while(1)
		{
			if (strcmp("q\n", ((ARGS*)args)->buffer) == 0)
			{
				break;
			}
			while(((ARGS*)args)->write == 0)
			{
				((ARGS*)args)->bufPtr = ((ARGS*)args)->buffer;
				if (strcmp("q\n", ((ARGS*)args)->buffer) == 0)
				{
					break;
				}
				while((*((ARGS*)args)->bufPtr) != '\0')
				{
					if((*((ARGS*)args)->bufPtr) == '\n')
					{
						fprintf(((ARGS*)args)->f, "\n");
						((ARGS*)args)->doneReading = 1;
						(*((ARGS*)args)->bufPtr) = '\n';
						memset(((ARGS*)args)->buffer, 0, 11); // just in case..
						break;
					}
					fprintf(((ARGS*)args)->f, "%c", (*((ARGS*)args)->bufPtr));
					((ARGS*)args)->bufPtr++;
				}

				((ARGS*)args)->write = 1;
			}
		}
		
		fclose(((ARGS*)args)->f);
	}
	return 0;
}
