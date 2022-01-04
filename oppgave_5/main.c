#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "./include/workerThread.h"

int main(int argc, char *argv[])
{
	pthread_t pT1;
	ARGS *args = NULL;
	args = malloc(sizeof(ARGS));
	if (args == NULL)
	{
		printf("Error: Allocation failure\n");
		return 1;
	}
	args->write = 1;	
	args->doneReading = 1;
	memset(args->buffer, 0, 11); 
	pthread_create(&pT1, NULL, getStringIntoFile, (void *)args);
	
	while(1)
	{
		if (strcmp("q\n", args->buffer) == 0)
		{
			break;
		}
		while(args->write == 1)
		{
			if (args->doneReading == 1)
			{
				printf("Enter a text string ('q' to quit)\n");
			}
			args->doneReading = 0;
			if(fgets(args->buffer, 10, stdin) != NULL)
			{
				args->buffer[10] = '\0';
				args->write = 0;	
			}
			else
			{
				printf("Error.. Not reading time :(\n");
			}
		}
	}

	pthread_join(pT1, NULL);
	free(args);
	args = NULL;
	
	printf("End of program.\n");
	return 0;
}
