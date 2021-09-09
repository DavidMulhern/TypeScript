#include<stdio.h>
#include<string.h>
#include"LinkedList.h"
#include"verifyUser.h"


void main()
{
	FILE* filePoint;

	char tempUser[20];
	char tempPass[20];
	char arrayNames[4][10];
	char arrayPass[4][10];
	int i = 0;
	int grantAccess = 0;
	char userChoice[50];
	int firstEntry = 0;
	int totalNodes = 0;
	int nodeToGo;
	int parsedChoice;

	// pointers	
	customerT* HEAD = NULL; // First point of the linked list
	customerT* temp; // Temporary pointer
	customerT* temp2; // Used for travesing through the list

	filePoint = fopen("loginDetails.txt", "r");
	if (filePoint == NULL)
	{
		printf("Sorry the file could not be opened\n");
	}
	else {

		while (!feof(filePoint)) // Populate array with all valid login details from: loginDetails.txt
		{
			fscanf(filePoint, "%s", tempUser);
			fscanf(filePoint, "%s", tempPass);
			strcpy(arrayNames[i], tempUser);
			strcpy(arrayPass[i], tempPass);
			i++;
		}
		fclose(filePoint); // Close file
	}

	printf("******************************************\n");
	printf("* Welcome to the ABC Cinema LTD database *\n");
	printf("******************************************\n\n");

	grantAccess = verifyLogin(arrayNames, arrayPass); // Returns 1 when user login is successful

	loadCustomers(&HEAD); // function that leads to customer being loaded from the customer.txt file
	if (HEAD != NULL)
	{
		firstEntry = 1; // This controls if the initial node needs to be created, it will skip to sorted entry if nodes get populated from file
	}


	if (grantAccess == 1) // Access granted and launches into the menu for the user 
	{
		printf("To add a customer, please press: 1\n");
		printf("To display all customers to screen, please press: 2\n");
		printf("To search and display a customer, please press: 3\n");
		printf("To update a customers details, please press: 4\n");
		printf("To delete a customer from database, please press: 5\n");
		printf("To generate statistics, please press: 6\n");
		printf("To print customer details to file, please press: 7\n");
		printf("To list customers by their year born, please press: 8\n");
		printf("To exit, please press: -1\n");
		scanf("%s", userChoice);
		parsedChoice = parseCheck(userChoice); // This will parse entry into integer. Same function used several times in sub menus.

		while (parsedChoice != -1)
		{
			switch (parsedChoice) {
			case 1:
				if (firstEntry == 0)
				{
					addCustomerAtStart(&HEAD); // This is used only when there is initial nodes from the saved file
					firstEntry = 1;
				}
				else {
					addCustomerSorted(&HEAD, HEAD); // This will add and order by DOB
				}
				break;
			case 2:
				display(HEAD); // Displays all nodes to screen - Sorted
				break;
			case 3:
				search(HEAD); // Search by PPS and display to screen
				break;
			case 4:
				updateCustomer(HEAD); // Search by PPS and alter the targeted node 
				break;
			case 5:
				totalNodes = length(HEAD); // Get the total of nodes in the linked list
				nodeToGo = getLoc_PPS(HEAD); // get the location of a node - this will in turn be used to delete in the middle 
				if (nodeToGo == totalNodes)
				{
					deleteAtEnd(HEAD); // delete at end
				}
				else if (nodeToGo == 1)
				{
					deleteAtStart(&HEAD); // delete at start 
				}
				else {
					deleteintheMiddle(HEAD, nodeToGo); // delete in middle, this uses the getLoc_PPS() to determine which node
				}
				break;
			case 6:
				genStats(); // This will generate the statistics of what percentage came from what area
				break;
			case 7:
				writeToFile(HEAD); // Human eye friendly report
				break;
			case 8:
				display(HEAD); // // Displays all nodes to screen - Sorted
				break;
			case -1:
				grantAccess = 0;
				parsedChoice = -1; // User decides to leave
				break;
			default:
				printf("Invalid Entry\n");
			}

			printf("\nTo add a customer, please press: 1\n");
			printf("To display all customers to screen, please press: 2\n");
			printf("To search and display a customer, please press: 3\n");
			printf("To update a customers details, please press: 4\n");
			printf("To delete a customer from database, please press: 5\n");
			printf("To generate statistics, please press: 6\n");
			printf("To print customer details to file, please press: 7\n");
			printf("To list customers by their year born, please press: 8\n");
			printf("To exit, please press: -1\n");
			scanf("%s", userChoice);
			parsedChoice = parseCheck(userChoice);
		}
	}

	saveCustomers(HEAD); // Before application it creates a backup of the current nodes, which will be retrieved once app gets used again 
	printf("\n==============END===============\n"); // Informs user the app has been closed

} // Author: David Mulhern - G00268549

