#ifndef _LIST_H_
#define _LIST_H_

typedef struct _NODE {
	struct _NODE *next;
	struct _NODE *prev;
	char pszItem[32];
	int iNum;
	float fPrice;

} NODE;

NODE *createItem();
void appendItem(NODE **head); 
NODE *createNode(int num);
void appendNode(NODE **head, int num);
void deleteLast(NODE **head);
void deleteItem(NODE **head, char *item);
void totalSum(NODE *head);
void printList(NODE *head);
int ifExistsAddOne(NODE **head, int num);
void printMenu();
void removeLastNode(NODE **head);
void removeByName(NODE **head, char *pszName);
void removeNode(NODE *node);
void deleteList(NODE *head);
int readInput(char str[], int max_length);
void flushInput();
void undo(NODE **head, char *latestItem);


#endif // ndef _LIST_H
