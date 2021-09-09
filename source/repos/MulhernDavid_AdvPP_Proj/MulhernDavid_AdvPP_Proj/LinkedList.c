#include "LinkedList.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

float _galwayCityCount = 0;
float _galwayCountyCount = 0;
float _connachtCount = 0;
float _otherAreaCount = 0;
float _outsideIrelandCount = 0;

// Ensures node entry is either top of list or sorted
void addCustomerSorted(customerT** top)
{
	customerT* temp;
	customerT* temp2;

	//Creating the new node
	temp = (customerT*)malloc(sizeof(customerT));
	printf("\nPlease enter customers PPS number\n");
	temp->custPPS = searchPPS(*top);
	printf("Please enter the customers first name\n");
	scanf("%s", temp->custFirstname);
	printf("Please enter the customers last name\n");
	scanf("%s", temp->custSurname);
	printf("Please enter customers year of birth\n");
	scanf("%d", &temp->custYear);
	printf("Please enter the customers email\n");
	strcpy(temp->custEmail, emailWithAt());
	printf("\nSelect an area from where the customer has travelled from\n");
	strcpy(temp->custArea, whatArea());
	printf("\nSelect the customers ticket type\n");
	strcpy(temp->custTicket, ticketType());
	printf("\nHow many trips does the customer take to the cinema per year\n");
	strcpy(temp->custTrips, cinTrips());
	printf("\nHow much does the customer roughly spend\n");
	strcpy(temp->custSpend, avgSpend());
	temp->NEXT = NULL;

	// Special case for top of list
	if (*top == NULL || (*top)->custYear >= temp->custYear)
	{
		temp->NEXT = *top;
		*top = temp;
	}
	else { // Special case for adding a node in a sorted way
		temp2 = *top;

		while (temp2->NEXT != NULL && temp2->NEXT->custYear < temp->custYear)
		{
			temp2 = temp2->NEXT;
		}
		temp->NEXT = temp2->NEXT;
		temp2->NEXT = temp;
	}
}

// Initial node if user starts with no saved data
void addCustomerAtStart(customerT** top)
{
	customerT* temp;

	//Creating the new node
	temp = (customerT*)malloc(sizeof(customerT));
	printf("\nPlease enter customers PPS number\n");
	scanf("%d", &temp->custPPS);
	printf("Please enter the customers first name\n");
	scanf("%s", temp->custFirstname);
	printf("Please enter the customers last name\n");
	scanf("%s", temp->custSurname);
	printf("Please enter customers year of birth\n");
	scanf("%d", &temp->custYear);
	printf("Please enter the customers email\n");
	strcpy(temp->custEmail, emailWithAt());
	printf("\nSelect an area from where the customer has travelled from\n");
	strcpy(temp->custArea, whatArea());
	printf("\nSelect the customers ticket type\n");
	strcpy(temp->custTicket, ticketType());
	printf("\nHow many trips does the customer take to the cinema per year\n");
	strcpy(temp->custTrips, cinTrips());
	printf("\nHow much does the customer roughly spend\n\n");
	strcpy(temp->custSpend, avgSpend());

	temp->NEXT = *top; //*top currently has the address of the first node
	*top = temp;
}

// Will loop through list and display details on screen
void display(customerT* top)
{
	customerT* temp;
	if (top == NULL)
		printf("The list is empty\n"); // Catch in case list is empty
	else
	{
		temp = top;

		while (temp != NULL)
		{
			printf("\n---------------------------------------------\n");
			printf("Customer pps: %d\n", temp->custPPS);
			printf("First Name: %s\n", temp->custFirstname);
			printf("Surename: %s\n", temp->custSurname);
			printf("Born in: %d\n", temp->custYear);
			printf("Email: %s\n", temp->custEmail);
			printf("Customer came from: %s\n", temp->custArea);
			printf("Ticket type: %s\n", temp->custTicket);
			printf("Customer attends cinema %s times per year\n", temp->custTrips);
			printf("Customer spends %s on average\n", temp->custSpend);
			printf("\n---------------------------------------------\n");
			temp = temp->NEXT;
		}
	}
}

// Iterates through the list, once a PPS match is confirmed the customer information is printed to screen
void search(customerT* top)
{
	customerT* temp;
	int userSearch;

	printf("Please enter the PPS number of the customer you are looking for:\n");
	scanf("%d", &userSearch);

	if (top == NULL)
		printf("The list is empty\n"); // Catch in case list is empty
	else
	{
		temp = top;

		while (temp != NULL)
		{
			//Move to the next node
			if (temp->custPPS == userSearch)
			{
				printf("\n*** Customer found ***\n\n");
				printf("\n---------------------------------------------\n");
				printf("Customer pps: %d\n", temp->custPPS);
				printf("First Name: %s\n", temp->custFirstname);
				printf("Surename: %s\n", temp->custSurname);
				printf("Born in: %d\n", temp->custYear);
				printf("Email: %s\n", temp->custEmail);
				printf("Customer came from: %s\n", temp->custArea);
				printf("Ticket type: %s\n", temp->custTicket);
				printf("Customer attends cinema %s times per year\n", temp->custTrips);
				printf("Customer spends %s on average\n", temp->custSpend);
				printf("\n---------------------------------------------\n");
			}
			temp = temp->NEXT;
		}
	}
}

// Function used to get a location for a specific PPS, in turn used to remove specific nodes in middle of the list
int getLoc_PPS(customerT* top)
{
	customerT* temp;
	int userSearch;
	int location = 1;

	printf("Please enter the PPS number of the customer you want to delete:\n");
	scanf("%d", &userSearch);

	if (top == NULL)
		printf("The list is empty\n"); // Catch in case list is empty
	else
	{
		temp = top;

		while (temp != NULL)
		{
			if (temp->custPPS == userSearch)
			{
				break;
			}
			temp = temp->NEXT;
			location++;
		}
	}
	return location;
}

// This function ensures every PPS entry is unique 
int searchPPS(customerT* top)
{
	customerT* temp;
	int searchPPS;
	temp = top;

	scanf("%d", &searchPPS);

	if (top == NULL)
		printf("The list is empty\n"); // Catch in case list is empty

	while (temp != NULL)
	{

		do
		{
			if (temp->custPPS == searchPPS)
			{
				printf("PPS number already in use. Try again\n");
				scanf("%d", &searchPPS);
			}
			else {
				return searchPPS;
			}

		} while (temp->custPPS == searchPPS); // remain in loop until unique PPS has been entered 
		temp = temp->NEXT;
	}
	return searchPPS; // Unique PPS entry is achieved
}

// Function to get the total number of nodes in a list
int length(customerT* top)
{
	customerT* temp;
	int length = 0;

	if (top == NULL) // returns zero value if empty
		return 0;

	else
	{
		temp = top;

		while (temp != NULL)
		{
			length++; // counter which will be returned
			temp = temp->NEXT;
		}
	}
	return length;
}

// The next three functions are for deleting nodes at end, start or middle
void deleteAtEnd(customerT* top)
{
	customerT* last;
	customerT* secondlast;

	last = top;

	if (top == NULL)
		printf("The list is empty\n");
	while (last->NEXT != NULL)
	{
		secondlast = last;
		last = last->NEXT;
	}

	secondlast->NEXT = NULL;
	areaTallyAdjust(last->custArea);
	free(last); // free the memory that was allocated to the node
	printf("\n\n*** Customer successfully deleted ***\n");
}
void deleteAtStart(customerT** top)
{
	customerT* temp;

	if (top == NULL)
		printf("The list is empty\n");

	temp = *top;
	*top = temp->NEXT;
	areaTallyAdjust(temp->custArea);
	free(temp); // free the memory that was allocated to the node
	printf("\n\n*** Customer successfully deleted ***\n");

}
void deleteintheMiddle(customerT* top, int nodeNum)
{
	customerT* last;
	customerT* secondlast;
	int location = 1;
	int removed = 0;

	last = top;

	if (top == NULL)
		printf("The list is empty\n");
	while (last->NEXT != NULL)
	{
		if (location == nodeNum)
		{
			//This is the node to remove as we have a match
			secondlast->NEXT = last->NEXT;
			areaTallyAdjust(last->custArea);
			free(last);
			removed = 1;
			printf("\n\n*** Customer successfully deleted ***\n");
			break; // Job done, leave the loop
		}
		secondlast = last;
		last = last->NEXT;
		location++;
	}

	if (removed == 0)
	{
		printf("\n*** The PPS number could not be found ***\n"); // User notified if PPS was not found
	}
}

// Iterates through the list, once a PPS match is confirmed, user instructed to create a new entry in its place 
void updateCustomer(customerT* top)
{
	customerT* temp;
	int search = 0;
	int userSearch;
	temp = top;

	printf("Please enter the PPS number of the customer to update their details:\n");
	scanf("%d", &userSearch);

	if (top == NULL)
		printf("The list is empty\n");
	while (temp != NULL)
	{
		if (temp->custPPS == userSearch) // Node found and the update process begins
		{
			printf("Please enter customers PPS number\n");
			temp->custPPS = searchPPS(top);
			printf("Please enter the customers first name\n");
			scanf("%s", temp->custFirstname);
			printf("Please enter the customers last name\n");
			scanf("%s", temp->custSurname);
			printf("Please enter customers year of birth\n");
			scanf("%d", &temp->custYear);
			printf("Please enter the customers email\n");
			strcpy(temp->custEmail, emailWithAt());
			areaTallyAdjust(temp->custArea); // remove the area from global counters
			printf("\nSelect an area from where the customer has travelled from\n");
			strcpy(temp->custArea, whatArea()); 
			printf("\nSelect the customers ticket type\n");
			strcpy(temp->custTicket, ticketType());
			printf("\nHow many trips does the customer take to the cinema per year\n");
			strcpy(temp->custTrips, cinTrips());
			printf("\nHow much does the customer roughly spend\n");
			strcpy(temp->custSpend, avgSpend());
			search = 1;
			return;
		}
		temp = temp->NEXT;
	}

	if (search == 0)
		printf("\n*** No match found for PPS number entered ***\n");
}

// This function writes the report.txt - This is a "human eye" friendly report 
void writeToFile(customerT* top)
{
	customerT* temp2;
	FILE* outp;
	outp = fopen("report.txt", "w");

	// Ensure file ready
	if (outp == NULL)
	{
		printf("Sorry the file could not be opened\n");
	}
	else {
		// Writing to file 
		temp2 = top;
		while (temp2 != NULL)
		{
			fprintf(outp, "\n--------------------------------------------------");
			fprintf(outp, "\nCustomer pps: %d", temp2->custPPS);
			fprintf(outp, "\nFirst Name: %s", temp2->custFirstname);
			fprintf(outp, "\nSurename: %s", temp2->custSurname);
			fprintf(outp, "\nBorn in: %d", temp2->custYear);
			fprintf(outp, "\nEmail: %s", temp2->custEmail);
			fprintf(outp, "\nCustomer came from: %s", temp2->custArea);
			fprintf(outp, "\nTicket type: %s", temp2->custTicket);
			fprintf(outp, "\nCustomer attends cinema %s times per year", temp2->custTrips);
			fprintf(outp, "\nCustomer spends %s on average", temp2->custSpend);
			fprintf(outp, "\n--------------------------------------------------");
			temp2 = temp2->NEXT;

		}
		printf("\n~~~~~~~~~ Write report to file complete ~~~~~~~~~\n"); // Confirmation for user
	}
	fclose(outp); // Close file
}

// Function returns the user choice and makes sure correct number entered, it will also add to the above global variables which are needed for the statistics function
char* whatArea()
{
	char userEntry[50];
	int parsedChoice;
	char area[30];

	do
	{
		printf("If the customer travelled from Galway City, press: 1\n");
		printf("If the customer travelled from Galway County, press: 2\n");
		printf("If the customer travelled from Connacht, press: 3\n");
		printf("If the customer travelled from other areas of Ireland, press: 4\n");
		printf("If the customer travelled from outside of Ireland, press: 5\n");
		scanf("%s", userEntry);
		parsedChoice = parseCheck(userEntry);

		switch (parsedChoice) {
		case 1:
			_galwayCityCount++;
			strcpy(area, "Galway");
			return;
		case 2:
			_galwayCountyCount++;
			strcpy(area, "Galway County");
			return;
		case 3:
			_connachtCount++;
			strcpy(area, "Connacht");
			return;
		case 4:
			_otherAreaCount++;
			strcpy(area, "Other Area, Ireland");
			return;
		case 5:
			_outsideIrelandCount++;
			strcpy(area, "Outside Ireland");
			return;
		default:
			printf("Invalid Entry\n");
		}

	} while (parsedChoice < 1 || parsedChoice > 5);
	return area;
}

// Function returns the user choice and makes sure correct number entered
char* ticketType()
{
	char userEntry[50];
	int parsedChoice;
	char ticket[30];

	do
	{
		printf("Normal ticket, press: 1\n");
		printf("Luxury ticket, press: 2\n");
		scanf("%s", userEntry);
		parsedChoice = parseCheck(userEntry);

		switch (parsedChoice) {
		case 1:
			strcpy(ticket, "Normal ticket");
			return;
		case 2:
			strcpy(ticket, "Luxury ticket");
			return;
		default:
			printf("Invalid Entry\n");
		}

	} while (parsedChoice < 1 || parsedChoice > 2);

	return ticket;
}

// Function returns the user choice and makes sure correct number entered
char* cinTrips()
{
	char userEntry[50];
	int parsedChoice;
	char tripDesc[30];

	do
	{
		printf("Less than three, press: 1\n");
		printf("Less than five, press: 2\n");
		printf("More than five, press: 3\n");
		scanf("%s", userEntry);
		parsedChoice = parseCheck(userEntry);

		switch (parsedChoice) {
		case 1:
			strcpy(tripDesc, "Less than three");
			return;
		case 2:
			strcpy(tripDesc, "Less than five");
			return;
		case 3:
			strcpy(tripDesc, "More than five");
			return;
		default:
			printf("Invalid Entry\n");
		}

	} while (parsedChoice < 1 || parsedChoice > 3);
	return tripDesc;
}

// Function returns the user choice and makes sure correct number entered
char* avgSpend()
{
	char userEntry[50];
	int parsedChoice;
	char average[30];

	do
	{
		printf("Nothing, press: 1\n");
		printf("Less than 5 euro, press: 2\n");
		printf("Less than 10 euro, press: 3\n");
		printf("More than 10 euro, press: 4\n");
		scanf("%s", userEntry);
		parsedChoice = parseCheck(userEntry);

		switch (parsedChoice) {
		case 1:
			strcpy(average, "Nothing");
			return;
		case 2:
			strcpy(average, "Less than 5 euro");
			return;
		case 3:
			strcpy(average, "Less than 10 euro");
			return;
		case 4:
			strcpy(average, "More than 10 euro");
			return;
		default:
			printf("Invalid Entry\n");
		}

	} while (parsedChoice < 1 || parsedChoice > 4);
	return average;
}
// Function returns the email address. This function won't return unless an '@' symbol is present 
char* emailWithAt()
{
	char email[30];
	char checkString[30];
	char* find;

	scanf("%s", email);
	strcpy(checkString, email); // I made a copy of the user entry here, because the strstr() removes the part of the string present before the '@' 
	find = strstr(checkString, "@");

	do
	{
		if (find != NULL)
		{
			return email; // return the email if @ is present and break loop
		}
		else {
			printf("Error! emails must contain an @ symbol - Please enter your email again\n");
			scanf("%s", email);
			strcpy(checkString, email);
			find = strstr(checkString, "@");
		}
	} while (find == NULL);
	return email; // do while ended and email returned with '@' present 
}

// Function which is used in node deletion, used to adjust the values in the global variables 
void areaTallyAdjust(char areaDef[])
{
	if (strcmp(areaDef, "Galway") == 0)
	{
		_galwayCityCount--;
	}
	else if (strcmp(areaDef, "Galway County") == 0)
	{
		_galwayCountyCount--;
	}
	else if (strcmp(areaDef, "Connacht") == 0)
	{
		_connachtCount--;
	}
	else if (strcmp(areaDef, "Other Area, Ireland") == 0)
	{
		_otherAreaCount--;
	}
	else if (strcmp(areaDef, "Outside Ireland") == 0)
	{
		_outsideIrelandCount--;
	}
	else
	{
		printf("\n ERROR");
	}
}

// This function will populate the global counters when customer details are loaded from file
void onLoadTallyAdjust(char areaDef[])
{
	if (strcmp(areaDef, "Galway") == 0)
	{
		_galwayCityCount++;
	}
	else if (strcmp(areaDef, "Galway County") == 0)
	{
		_galwayCountyCount++;
	}
	else if (strcmp(areaDef, "Connacht") == 0)
	{
		_connachtCount++;
	}
	else if (strcmp(areaDef, "Other Area, Ireland") == 0)
	{
		_otherAreaCount++;
	}
	else if (strcmp(areaDef, "Outside Ireland") == 0)
	{
		_outsideIrelandCount++;
	}
	else
	{
		printf("\n ERROR");
	}
}

// This will show the % of the areas the customers came from on screen
void genStats()
{
	float totalTix = 0;
	totalTix = _galwayCityCount + _galwayCountyCount + _connachtCount + _otherAreaCount + _outsideIrelandCount;

	if (totalTix != 0)
	{
		printf("\n********************************************\n");
		printf("************ Statistic report **************\n");
		printf("********************************************\n");
		printf("* Galway City perecentage is: %.2f             \n", (_galwayCityCount / totalTix) * 100);
		printf("* Galway County perecentage is: %.2f           \n", _galwayCountyCount / totalTix * 100);
		printf("* Connacht perecentage is: %.2f         \n", _connachtCount / totalTix * 100);
		printf("* Othe areas of Ireland perecentage is: %.2f        \n", _otherAreaCount / totalTix * 100);
		printf("* Outside Ireland perecentage is: %.2f  \n", _outsideIrelandCount / totalTix * 100);
		printf("********************************************\n\n");
	}
	// just put a catch here in case list is empty 
	else {
		printf("\n********************************************\n");
		printf("************ REPORT EMPTY  *****************\n");
		printf("************ ADD ENTRIES  ******************\n");
		printf("********************************************\n");
	}
}

// I opted to break each string for the area/ticket/trips/spend into single strings, to make it easier when reading the file back in again (Save/Load)
// You can see in the four functions below the saveCustomers(), that I essentially transalated them into single words. This made life a lot easier when reading the file back in
// Step 1: Translate my 3 to 4 word strings into one single word
// Step 2: write each word to file
// Step 3: Read in single words - loadCustomers()
// Step 4: translate them back into original strings and populate node accordingly 
void saveCustomers(customerT* top)
{
	customerT* temp2;
	FILE* outp;

	int aroundAgain = 0;
	char smallArea[30];
	char smallTicket[30];
	char smallTrips[30];
	char smallSpend[30];

	outp = fopen("customer.txt", "w");

	// Ensure file ready
	if (outp == NULL)
	{
		printf("Sorry the file could not be opened\n");
	}
	else {
		// Writing to file 
		temp2 = top;
		while (temp2 != NULL)
		{
			if (aroundAgain == 1) // Something I came up with just to ensure the file writer doesn't leave a blank new line at EOF once complete
			{
				fprintf(outp, "\n%d", temp2->custPPS); 
			}
			else {
				fprintf(outp, "%d", temp2->custPPS);
			}
			fprintf(outp, "\n%s", temp2->custFirstname);
			fprintf(outp, "\n%s", temp2->custSurname);
			fprintf(outp, "\n%d", temp2->custYear);
			fprintf(outp, "\n%s", temp2->custEmail);
			strcpy(smallArea, shortArea(temp2->custArea)); // Translate function
			fprintf(outp, "\n%s", smallArea);
			strcpy(smallTicket, shortTicket(temp2->custTicket)); // Translate function
			fprintf(outp, "\n%s", smallTicket);
			strcpy(smallTrips, shortTrip(temp2->custTrips)); // Translate function
			fprintf(outp, "\n%s", smallTrips);
			strcpy(smallSpend, shortSpend(temp2->custSpend)); // Translate function
			fprintf(outp, "\n%s", smallSpend);
			temp2 = temp2->NEXT;
			aroundAgain = 1;
		}
		printf("\n~~~~~~~~~ Customers saved to file ~~~~~~~~~\n"); // Confirmation for user
	}
	fclose(outp); // Close file
}
// These four functions below are all used to translate sentances into one word strings before written to file
char* shortArea(char makeShort[])
{

	if (strcmp(makeShort, "Galway") == 0)
	{
		return "galway";
	}
	else if (strcmp(makeShort, "Galway County") == 0)
	{
		return "gCounty";
	}
	else if (strcmp(makeShort, "Connacht") == 0)
	{
		return "connacht";
	}
	else if (strcmp(makeShort, "Other Area, Ireland") == 0)
	{
		return "otherAreaIre";
	}
	else if (strcmp(makeShort, "Outside Ireland") == 0)
	{
		return "outsideIre";
	}
	else {
		return "ERROR";
	}
}
char* shortTicket(char makeShort[])
{
	if (strcmp(makeShort, "Normal ticket") == 0)
	{
		return "normTic";
	}
	else if (strcmp(makeShort, "Luxury ticket") == 0)
	{
		return "luxTic";
	}
	else {
		return "ERROR";
	}
}
char* shortTrip(char makeShort[])
{
	if (strcmp(makeShort, "Less than three") == 0)
	{
		return "lessThree";
	}
	else if (strcmp(makeShort, "Less than five") == 0)
	{
		return "lessFive";
	}
	else if (strcmp(makeShort, "More than five") == 0)
	{
		return "moreFive";
	}
	else {
		return "ERROR";
	}
}
char* shortSpend(char makeShort[])
{
	if (strcmp(makeShort, "Nothing") == 0)
	{
		return "nothing";
	}
	else if (strcmp(makeShort, "Less than 5 euro") == 0)
	{
		return "lessFiveEur";
	}
	else if (strcmp(makeShort, "Less than 10 euro") == 0)
	{
		return "lessTenEur";
	}
	else if (strcmp(makeShort, "More than 10 euro") == 0)
	{
		return "moreTenEur";
	}
	else {
		return "ERROR";
	}
}

// Upon program launch, this will load in my single words, translate them back into original string sentances while populating the nodes
void loadCustomers(customerT** top)
{
	FILE* filePoint;
	customerT* temp;
	customerT* temp2;

	char tempArea[30];
	char tempTicket[20];
	char tempTrips[20];
	char tempSpend[20];


	filePoint = fopen("customer.txt", "r");
	if (filePoint == NULL)
	{
		printf("*** No previous records detected ***\n\n");
	}
	else {

		// First node is added to start of the list, hence it being outside of the while(!feof(filepoint))
		temp = (customerT*)malloc(sizeof(customerT));
		fscanf(filePoint, "%d", &temp->custPPS);
		fscanf(filePoint, "%s", temp->custFirstname);
		fscanf(filePoint, "%s", temp->custSurname);
		fscanf(filePoint, "%d", &temp->custYear);
		fscanf(filePoint, "%s", temp->custEmail);
		fscanf(filePoint, "%s", tempArea);
		strcpy(temp->custArea, realArea(tempArea));
		onLoadTallyAdjust(temp->custArea);
		fscanf(filePoint, "%s", tempTicket);
		strcpy(temp->custTicket, realTicket(tempTicket));
		fscanf(filePoint, "%s", tempTrips);
		strcpy(temp->custTrips, realTrip(tempTrips));
		fscanf(filePoint, "%s", tempSpend);
		strcpy(temp->custSpend, realSpend(tempSpend));

		temp->NEXT = *top; //*top currently has the address of the first node 
	     //in the list which become the second node when temp is added infront of it
		*top = temp;

		
		while (!feof(filePoint)) // Populate more nodes with remaining information saved on: loginDetails.txt 
		{
			//Creating the new node
			temp = (customerT*)malloc(sizeof(customerT));
			fscanf(filePoint, "%d", &temp->custPPS);
			fscanf(filePoint, "%s", temp->custFirstname);
			fscanf(filePoint, "%s", temp->custSurname);
			fscanf(filePoint, "%d", &temp->custYear);
			fscanf(filePoint, "%s", temp->custEmail);
			fscanf(filePoint, "%s", tempArea);
			strcpy(temp->custArea, realArea(tempArea));
			onLoadTallyAdjust(temp->custArea);
			fscanf(filePoint, "%s", tempTicket);
			strcpy(temp->custTicket, realTicket(tempTicket));
			fscanf(filePoint, "%s", tempTrips);
			strcpy(temp->custTrips, realTrip(tempTrips));
			fscanf(filePoint, "%s", tempSpend);
			strcpy(temp->custSpend, realSpend(tempSpend));
			temp->NEXT = NULL;

			//Finding the last node
			temp2 = *top;
			while (temp2->NEXT != NULL)
			{
				temp2 = temp2->NEXT;
			}

			temp2->NEXT = temp;
		}
		fclose(filePoint); // Close file
	}

}

// The four below functions are all used to translate the one word string, back into their sentances 
char* realArea(char makeNormal[])
{
	if (strcmp(makeNormal, "galway") == 0)
	{
		return "Galway";
	}
	else if (strcmp(makeNormal, "gCounty") == 0)
	{
		return "Galway County";
	}
	else if (strcmp(makeNormal, "connacht") == 0)
	{
		return "Connacht";
	}
	else if (strcmp(makeNormal, "otherAreaIre") == 0)
	{
		return "Other Area, Ireland";
	}
	else if (strcmp(makeNormal, "outsideIre") == 0)
	{
		return "Outside Ireland";
	}
	else {
		return "ERROR";
	}
}
char* realTicket(char makeNormal[])
{
	if (strcmp(makeNormal, "normTic") == 0)
	{
		return "Normal ticket";
	}
	else if (strcmp(makeNormal, "luxTic") == 0)
	{
		return "Luxury ticket";
	}
	else {
		return "ERROR";
	}
}
char* realTrip(char makeNormal[])
{
	if (strcmp(makeNormal, "lessThree") == 0)
	{
		return "Less than three";
	}
	else if (strcmp(makeNormal, "lessFive") == 0)
	{
		return "Less than five";
	}
	else if (strcmp(makeNormal, "moreFive") == 0)
	{
		return "More than five";
	}
	else {
		return "ERROR";
	}
}
char* realSpend(char makeNormal[])
{
	if (strcmp(makeNormal, "nothing") == 0)
	{
		return "Nothing";
	}
	else if (strcmp(makeNormal, "lessFiveEur") == 0)
	{
		return "Less than 5 euro";
	}
	else if (strcmp(makeNormal, "lessTenEur") == 0)
	{
		return "Less than 10 euro";
	}
	else if (strcmp(makeNormal, "moreTenEur") == 0)
	{
		return "More than 10 euro";
	}
	else {
		return "ERROR";
	}

}

// This function is always called when a customer presses a number as an entry. It parses entries into integer values 
int parseCheck(char inCheck[50])
{
	int afterParse;
	sscanf(inCheck, "%d", &afterParse);

	return afterParse;
}
// Author: David Mulhern - G00268549