#include <stdio.h>
#include <string.h>
#include "./include/list.h"
#include "./include/pgdbglog.h"

extern char *latest;

// Debug mode on/off
int glob_bTraceEnabled = 0;

int main(int argc, char *argv[])
{
	int num;
	char command[32];
	char toRemove[32];
	NODE *head = NULL;
	// Program running while true
	while(1)
	{
		num = 0;
		memset(command, 0, 32);
		memset(toRemove, 0, 32);
		printf("Enter a command: ('h' for help)\n");
		if (readInput(command, 32) < 0) 
		{
			pgerror("Input error.\n");
			return 1;
		}
		if (strcmp("q", command) == 0)
		{
			deleteList(head); // frees all allocated
			printf("Quitting!\n");
			break;
		}
		else if (strcmp("h", command) == 0)
		{
			printf("Enter command or make an order\n"
					"Commands: \n"
					"h - Help\n"
					"q - Quit\n"
					"p - Prints the receipt\n"
					"add - To start adding an item\n"
					"sum - Prints out the total sum of the receipt\n\n"
					"menu - Prints out the menu\n"
					"To add an item from the menu: Type a number (1-5).\n"
					"undo - Removes the last item added to the list\n"
					"remove last - Removes all of the last item on the list\n"
					"remove [ItemName] - Remove a specific item\n"
					"delete list - Removes all items from the list\n");
		}
		else if (strcmp("menu", command) == 0)
		{
			printMenu();	
		}
		else if (strcmp("sum", command) == 0)
		{
			totalSum(head);	
		}
		else if (strcmp("add", command) == 0)
		{
			printf("Addfunction about to begin\n");
			if(head == NULL)
			{
				head = createItem();
				if (head == NULL)
				{
					pgerror("Failed to create a list\n");
					return 1;
				}
			}
			else
			{
				appendItem(&head);	
			}
			continue;
		}
		else if (strcmp("undo", command) == 0)
		{
			undo(&head, latest);	
		}
		else if (strcmp("remove last", command) == 0)
		{
			removeLastNode(&head);	
		}
		else if (strcmp("delete list", command) == 0)
		{
			deleteList(head);	
			head = NULL;
		}
		else if (strcmp("p", command) == 0)
		{
			printList(head);	
		}
		else if (sscanf(command, "%d", &num) != 0)
		{
			if(head == NULL)
			{
				head = createNode(num);
			}
			else
			{
				appendNode(&head, num);	
			}
		}
		else if (sscanf(command, "remove %s", toRemove) != 0)
		{
			removeByName(&head, toRemove);
		}
		else
		{
			printf("Error: Unknown command.\n");
		}
	}
	return 0;
}
