#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/list.h"
#include "./include/pgdbglog.h"

/* Items Prices*/
#define F_BANANA_PRICE 2.4
#define F_APPLE_PRICE 1.9
#define F_COFFEE_PRICE 2.5
#define F_CAKE_PRICE 3.2
#define F_NEWSPAPER_PRICE 5.3

// Global variable to store latest item added to the list
char *latest = NULL;

// Clear out stdin
void flushInput()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

// Function to read input and clear extra input from stdin
int readInput(char str[], int max_length)
{
	char c;
	int i = 0;
	int reading = 1;
	while(reading)
	{
		c = getchar();
		// Slutt å lese hvis det kommer enter eller end of file
		if((c == '\n') || (c == EOF)) reading = 0; 
		// Hvis lengden er nådd, ignorer input, men spar plass til \0
		else if(i < max_length - 1)
		{
			str[i] = c;
			i++;
		}
	}
	str[i] = '\0';
	return i;	
}

void fixDesimalSymbol(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == ',')
		{
			str[i] = '.';
		}
		i++;
	}
}

//////////////////////
/** LIST FUNCTIONS **/
//////////////////////

/* ADD NODE FUNCTIONS */
NODE *createItem()
{
	NODE *newNode = NULL;
	newNode = malloc(sizeof(NODE));
	char buf[20];
	if(newNode != NULL)
	{
		newNode->next = NULL;
		newNode->prev = NULL;

		printf("What item would you like to add?\n");
		if (readInput(buf, 20) < 0) 
		{
			pgerror("Input error when creating item name.\n");
			return NULL;
		}
		strcpy(newNode->pszItem, buf);
		latest = newNode->pszItem;
		while(1)
		{
			memset(buf, 0, 20);
			printf("To what price?\n");
			if(readInput(buf, 20) > 0)
			{
				fixDesimalSymbol(buf);
				if (sscanf(buf, "%f", &newNode->fPrice) < 0)
				{
					pgerror("Input error when creating item price.\n");
					return NULL;
				}
				if (newNode->fPrice > 0 && newNode->fPrice <= 9999) break;
				printf("Enter price (1-9999):\n");
			}
		}
		while(1)
		{
			memset(buf, 0, 20);
			printf("How many would you like to add?\n");
			if(readInput(buf, 20) > 0)
			{
				if (sscanf(buf, "%d", &newNode->iNum) < 0)
				{
					pgerror("Input error when creating item quantity.\n");
					return NULL;
				}
				if (newNode->iNum > 0 && newNode->iNum <= 99) break;
				printf("Enter quantity (1-99):\n");	
			}
		}
		printf("Added 1 %s to the list!\n", newNode->pszItem);
		newNode->fPrice = newNode->fPrice * newNode->iNum;		
	}
	return newNode;
}

void appendItem(NODE **head)
{
	if (*head == NULL)
	{
		pgerror("Cant add to list. List is empty\n");
		return;
	}
	
	NODE *newNode = createItem(); 
	
	NODE *curr = *head;
	while(curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = newNode;
	newNode->prev = curr;
	newNode->next = NULL;
}

NODE *createNode(int num)
{
	if(num < 1 || num > 5)
	{
		printf("Error: Input error. To order: enter a number (1-5)\n");
		return NULL;
	}

	NODE *newNode = NULL;
	newNode = malloc(sizeof(NODE));
	if(newNode != NULL)
	{
		newNode->next = NULL;
		newNode->prev = NULL;
		switch(num)
		{
			case 1:
				strcpy(newNode->pszItem, "banana");
				latest = newNode->pszItem;
				newNode->iNum = 1;
				newNode->fPrice = F_BANANA_PRICE;
				break;
			case 2:
				strcpy(newNode->pszItem, "apple");
				latest = newNode->pszItem;
				newNode->iNum = 1;
				newNode->fPrice = 1.9;
				break;
			case 3:
				strcpy(newNode->pszItem, "coffee");
				latest = newNode->pszItem;
				newNode->iNum = 1;
				newNode->fPrice = 2.5;
				break;
			case 4:
				strcpy(newNode->pszItem, "cake");
				latest = newNode->pszItem;
				newNode->iNum = 1;
				newNode->fPrice = 3.2;
				break;
			case 5:
				strcpy(newNode->pszItem, "newspaper");
				latest = newNode->pszItem;
				newNode->iNum = 1;
				newNode->fPrice = 5.3;
				break;
			default:
				printf("Error: Selection error, please try again.\n");
		}
		printf("Added 1 %s to the list!\n", newNode->pszItem);
	}
	else
	{
		pgerror("Allocation failure.\n");
	}

	return newNode;
}


void appendNode(NODE **head, int num)
{
	if(num < 1 || num > 5)
	{
		printf("Error: Input error. To order: enter a number (1-5)\n");
		return;
	}

	// Check if already on list, then add one more.
	if (ifExistsAddOne(head, num) == 1)
	{
		return;
	}

	NODE *newNode = createNode(num);
	NODE *curr = *head;
	while(curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = newNode;
	newNode->prev = curr;
	newNode->next = NULL;
}

int ifExistsAddOne(NODE **head, int num)
{
	int exists = 0;
	if (head == NULL)
	{
		pgerror("Head is NULL\n");
	}
	else
	{
		NODE *curr = *head;
		while(curr != NULL)
		{
			if((strcmp(curr->pszItem, "banana") == 0) && num == 1)
			{
				exists = 1;
				curr->iNum++;
				latest = curr->pszItem;
				curr->fPrice += F_BANANA_PRICE;
				printf("Added 1 more %s to the list\n", curr->pszItem);
			}
			else if((strcmp(curr->pszItem, "apple") == 0) && num == 2)
			{
				exists = 1;
				curr->iNum++;
				latest = curr->pszItem;
				curr->fPrice += F_APPLE_PRICE;
				printf("Added 1 more %s to the list\n", curr->pszItem);
			}
			else if((strcmp(curr->pszItem, "coffee") == 0) && num == 3)
			{
				exists = 1;
				curr->iNum++;
				latest = curr->pszItem;
				curr->fPrice += F_COFFEE_PRICE;
				printf("Added 1 more %s to the list\n", curr->pszItem);
			}
			else if((strcmp(curr->pszItem, "cake") == 0) && num == 4)
			{
				exists = 1;
				curr->iNum++;
				latest = curr->pszItem;
				curr->fPrice += F_CAKE_PRICE;
				printf("Added 1 more %s to the list\n", curr->pszItem);
			}
			else if((strcmp(curr->pszItem, "newspaper") == 0) && num == 5)
			{
				exists = 1;
				curr->iNum++;
				latest = curr->pszItem;
				curr->fPrice += F_NEWSPAPER_PRICE;
				printf("Added 1 more %s to the list\n", curr->pszItem);
			}

			curr = curr->next;
		}
	}
	return exists;
}

/* REMOVE NODE FUNCTIONS */

void removeLastNode(NODE **head)
{
	if (*head == NULL)
	{
		printf("Error: List is empty\n");
		return;
	}
	else if ((*head)->next == NULL)
	{
		printf("Removed %s from the list. List is empty\n", (*head)->pszItem);
		free(*head);
		*head = NULL;
		
	}
	else
	{
		NODE *curr = *head;
		while(curr->next->next != NULL)
		{
			curr = curr->next;			
		}
		printf("Removed %s from the list.\n", curr->next->pszItem);

		NODE *toRemove = curr->next;
		curr->next = NULL;
		free(toRemove);
		toRemove = NULL;
		
	}
}

void removeNode(NODE *node)
{
	if (node->prev != NULL)
	{
		node->prev->next = node->next; 
	}
	if (node->next != NULL)
	{
		node->next->prev = node->prev;
	}
	free(node);
	node = NULL;
}

//Remove last added node
void undo(NODE **head, char *latestItem)
{
	if (latest == NULL)
	{
		printf("Error: You can only undo once\n");
		return;
	}
	removeByName(head, latestItem);
}

void removeByName(NODE **head, char *pszName)
{
	latest = NULL;
	if (*head == NULL)
	{
		printf("Error: List is empty\n");
		return;
	}
	else if (strcmp((*head)->pszItem, pszName) == 0)
	{
		if ((*head)->iNum > 1)
		{
			(*head)->iNum--;
			printf("Removed 1 %s from the list.\n", (*head)->pszItem);
			return;
		}
		else
		{
			printf("Removed 1 %s from the list.\n", (*head)->pszItem);
			NODE *temp = (*head);
			*head = (*head)->next;
			free(temp);
			temp = NULL;
		}
	}
	else
	{
		NODE *curr = *head;
		int exists = 0;
		while(curr != NULL)
		{
			if (strcmp(curr->pszItem, pszName) == 0)
			{
				printf("Removed 1 %s from the list.\n", curr->pszItem);
				if (curr->iNum > 1)
				{
					exists = 1;
					curr->iNum--;
				}
				else
				{
					exists = 1;
					NODE *toRemove = curr;
					removeNode(toRemove);
				}
				return;
			}
			curr = curr->next;			
		}
		if(exists == 0)
		{
			printf("Could not find any %s on the list\n", pszName);
		}
	}
}

void deleteList(NODE *head)
{
	NODE *toRemove = NULL;
	while(head != NULL)
	{
		toRemove = head;
		head = head->next;
		free(toRemove);
	}
	printf("All items have been removed from the list\n");
}

/*OTHER LIST FUNCTIONS*/

void printList(NODE *head)
{
	if (head == NULL)
	{
		printf("Error: List is empty\n");
	}
	else
	{
		while(head != NULL)
		{
			printf("%02dx %s\t\t$%.2f\n",
					head->iNum,
					head->pszItem,
					head->fPrice);
			head = head->next;
		}
	}
}

void totalSum(NODE *head)
{
	if (head == NULL)
	{
		printf("Error: List is empty\n");
	}
	else
	{
		float iSum = 0;
		while(head != NULL)
		{
			iSum += ((head->fPrice) * (head->iNum));

			head = head->next;
		}
		printf("Sum of all items: $%.2f\n", iSum);
	}
}

void printMenu()
{
	printf("Menu:\n"
		"1. Banana ($%.2f)\n" 
		"2. Apple ($%.2f)\n" 
		"3. Coffee ($%.2f)\n" 
		"4. Cake ($%.2f)\n" 
		"5. Newspaper ($%.2f)\n",
		F_BANANA_PRICE, F_APPLE_PRICE, F_COFFEE_PRICE, F_CAKE_PRICE, F_NEWSPAPER_PRICE);
}
