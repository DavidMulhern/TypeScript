
// my struct details
typedef struct NodeT_
{
	int custPPS;
	char custFirstname[20];
	char custSurname[20];
	int custYear;
	char custEmail[30];
	char custArea[30];
	char custTicket[20];
	char custTrips[20];
	char custSpend[20];
	struct NodeT_* NEXT;
}customerT;

// All the function prototypes for Source.c and LinkedList.c

void addCustomerAtStart(customerT** top);
void addCustomerSorted(customerT** top);
void display(customerT* top);
void search(customerT* top);
int searchPPS(customerT* top);
int getLoc_PPS(customerT* top);
int length(customerT* top);
void deleteAtEnd(customerT* top);
void deleteAtStart(customerT** top);
void deleteintheMiddle(customerT* top, int nodeNum);
void updateCustomer(customerT* top);
void writeToFile(customerT* top);
void areaTallyAdjust(char areaDef[]);
void onLoadTallyAdjust(char areaDef[]);
void genStats();

void saveCustomers(customerT* top);
void loadCustomers(customerT** top);

char* shortArea(char makeShort[]);
char* shortTicket(char makeShort[]);
char* shortTrip(char makeShort[]);
char* shortSpend(char makeShort[]);

char* realArea(char makeNormal[]);
char* realTicket(char makeNormal[]);
char* realTrip(char makeNormal[]);
char* realSpend(char makeNormal[]);

char* whatArea();
char* ticketType();
char* cinTrips();
char* avgSpend();
char* emailWithAt();

int parseCheck(char inCheck[50]);


// Author: David Mulhern - G00268549