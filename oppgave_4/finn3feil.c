#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _MYHTTP 
{ 
	int iHttpCode; 
	int iContentLength;
	bool bIsSuccess; 
	char szServer[32]; //burde det vært plass til flere karakterer for server navn ('16 / '32') 
	char szContentType[16]; 
	char szLastModified[32];
} MYHTTP;

// Funksjon for å samle header-data fra en http-response.
MYHTTP* ProcessHttpHeader(char *pszHttp) 
{
	char* pszPtr;
	MYHTTP* pHttp = (MYHTTP*)malloc(sizeof(MYHTTP));

	if (!pHttp) return NULL;

	memset(pHttp, 0, sizeof(MYHTTP));
	
	//setter iHttpCode
	pHttp->iHttpCode = atoi(pszHttp + strlen("HTTP/1.x "));
	if (pHttp->iHttpCode == 200) // skal være 2 '=' i en sammenligning ('='/'==') 
	{
		pHttp->bIsSuccess = true;
	}

	// Setter szServer
	pszPtr = strstr(pszHttp, "Server");
	if (pszPtr) 
	{
		pszPtr += 6; while (!isalpha(pszPtr[0]))pszPtr++;
		strchr(pszPtr, '\n')[0] = 0;
		strcpy(pHttp->szServer, pszPtr);
		pszPtr[strlen(pHttp->szServer)] = '\n';
	}

	// Setter szContentType
	pszPtr = strstr(pszHttp, "Content-Type");
	if (pszPtr) 
	{
		pszPtr += 12; while (!isalpha(pszPtr[0]))pszPtr++;
		strchr(pszPtr, '\n')[0] = 0;
		strncpy(pHttp->szContentType, pszPtr, 15);
		pszPtr[strlen(pHttp->szContentType)] = '\n';
	}

	// Setter iContentLength
	pszPtr = strstr(pszHttp, "Content-Length");
	if (pszPtr) 
	{
		pszPtr += 14; 
		while (!isdigit(pszPtr[0])) 
		{
			pszPtr++;
		}
		pHttp->iContentLength = atoi(pszPtr); // tok inn feil pointer ('pszHttp/pszPtr')
	}

	// Setter szLastModified
	pszPtr = strstr(pszHttp, "Last-Modified");
	if (pszPtr) 
	{
		pszPtr += 13; while (!isalpha(pszPtr[0]))pszPtr++;
		strchr(pszPtr, '\n')[0] = 0;
		strcpy(pHttp->szLastModified, pszPtr);
		pszPtr[strlen(pHttp->szLastModified)] = '\n';
	}

	//Returner struct
	return pHttp;
}

int main (int argc, char *argv[])
{
	// Hjemmesnekra eksempel på en httprespons
	char str[] = "HTTP/1.x 301 Moved Permanently\nServer: ECAcc (ska/F6E3)\nContent-Type: text/html\nContent-Length: 144\nLast-Modified: Wed, 21 Oct 2015 07:28:00 GMT\n\n";

	// Kjør strengen gjennom funksjonen og inn i en mthttp struct
	MYHTTP* pMyhttp = ProcessHttpHeader(str);

	// Print ut stringen og etterpå verdiene fra structen for sammenligning
	printf("INPUT STRING:\n%s", str);

	printf("MYHTTP STRUCT:\n");
	printf("Status Code: %d\n", pMyhttp->iHttpCode);
	printf("Server: %s\n", pMyhttp->szServer);
	printf("Content-Type: %s\n", pMyhttp->szContentType);
	printf("Content-Length: %d\n", pMyhttp->iContentLength);
	printf("Last-Modified: %s\n", pMyhttp->szLastModified);
	
	free(pMyhttp);
	pMyhttp = NULL;
	return 0;
}
