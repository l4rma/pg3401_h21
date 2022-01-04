#ifndef _WORKERTHREAD_H_
#define _WORKERTHREAD_H_

#include <stdio.h>

typedef struct _ARGS
{
	char buffer[11];
	FILE *f;
	int write;
	char *bufPtr;
	int doneReading;
} ARGS;

void* getStringIntoFile(void* args);

#endif // ndef __WORKERTHREAD_H_
