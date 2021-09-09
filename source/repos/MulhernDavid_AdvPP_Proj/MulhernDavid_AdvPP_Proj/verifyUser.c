#include "verifyUser.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

// Macros which assing keystrokes to ascii 
#define ENTER 13
#define TAB 9
#define BKSP 8
#define SPACE 32

int verifyLogin(char validNames[][10], char validPass[][10])
{
	char userName[20];
	char userPass[20];
	int userAccess = 0;

	printf("Please enter username\n");
	scanf("%s", userName);
	printf("Please enter password\n");
	strcpy(userPass, hidePW());

	while (userAccess != 1)
	{
		for (int j = 0; j < 3; j++) // Search through arrays and try get a match to gain access
		{
			if ((strcmp(validNames[j], userName) == 0) && (strcmp(validPass[j], userPass) == 0))
			{
				printf("\n\n***** Access Granted *****\n");
				userAccess = 1;
				break;
			}
		}
		if (userAccess != 1)
		{
			printf("\n\n***** Invalid username or password *****\n\n"); // Confirmation for user. try again
			printf("Please enter username\n");
			scanf("%s", userName);
			printf("Please enter password\n");
			strcpy(userPass, hidePW()); // calls the functio that will hide the password during entry 
		}
	}
	return userAccess;
}

char* hidePW() // hide password during entry
{
	char password[20];
	char ch;
	int i = 0;

	while (1) // Infinite loop essentially! 1 = true , This will terminate when user presses enter
	{
		ch = getch();
		if (ch == ENTER)
		{
			password[i] = '\0'; // close off the character array 
			break;
		}
		else if (ch == BKSP)
		{
			if (i > 0)
			{
				i--;
				printf("\b \b"); // Do this to delete the previous char entry 
			}
		}
		else if (ch == TAB || ch == SPACE) // This will ignore users pressing tab or space 
		{
			continue;
		}
		else {
			password[i] = ch;
			i++;
			printf("*"); // getch() naturally shows nothing as you type, using this to show a star
		}
	}
	return password;

}// Author: David Mulhern - G00268549