#include <stdio.h>	//standard input-output library
#include <stdlib.h> //standard C library
#include <string.h> //contains functions related to strings

#include "library.h" //header file with functions related to banking

// the following function prints the menu and takes the input from the user
short int getInput()
{
	printf("\nPlease refer to the menu below and enter your choice below:\n"); // Introduces the user to the menu

	// the following lines print the menu options
	printf("\t\t1.  Open an account\n");
	printf("\t\t2.  Display balance\n");
	printf("\t\t3.  Deposit\n");
	printf("\t\t4.  Withdraw\n");
	printf("\t\t5.  Exit\n");

	// the following prompts the user for input and reads the input from the user
	short int choice;

	printf("Please enter the index corresponding to your choice: ");
	scanf("%hd", &choice);

	return choice;
}

// the following code takes the PIN as input from user and checks validity
int returnPin()
{
	char pin[10];
	printf("Please enter your choice of PIN for the account: ");
	scanf("%s", pin);
	if (strlen(pin) != 4)
	{
		printf("It seems you have made a mistake, please enter a valid PIN and try again: ");
		scanf("%s", pin);
		if (strlen(pin) != 4)
		{
			printf("\nYou have failed to enter a valid PIN. Your PIN has been set to '0000'.\n");
			return 0;
		}
	}
	return atoi(pin);
}

// the following code checks the PIN entered by user for transacting
int checkPin()
{
	char pin[10];

	printf("Please enter you PIN: ");
	scanf("%s", pin);

	if (strlen(pin) != 4)
	{
		return -1;
	}
	else
	{
		return atoi(pin);
	}
}

int main()
{
	FILE *dataBase = fopen("bank.csv", "r"); //opens the file stream and checks if it exists
	init(dataBase);

	printf("Greetings,\nWelcome to The Bank.\n"); // displays a greeting message for the user

	while (1) // keeps on asking for input till 5 (exit) is received
	{
		short int choice;

		choice = getInput(); // takes the choice from user

		// the following is the code snippet if user chooses choice 1
		if (choice == 1)
		{
			char fullName[51];
			unsigned char accNum;
			char temp;

			printf("\nThanks for choosing The Bank for keeping your money safe\n");

			printf("\nPlease enter your full name: ");
			scanf("%c",&temp);
			scanf("%[^\n]%*c", fullName);

			accNum = new_account(fullName, returnPin());

			printf("\nYou have successfully opened an account (Acc Number: %hhu) with us. As a welcome bonus, $100 have been successfully credited to your account, stay safe and happy banking\n", accNum);
		}

		// the following is the code snippet if user chooses choice 2
		if (choice == 2)
		{
			unsigned char accNum;
			int pin;

			printf("\nPlease enter your account number: ");
			scanf("%hhu", &accNum);

			pin = checkPin();

			display_balance(accNum, pin);
		}

		// the following is the code snippet if user chooses choice 3
		if (choice == 3)
		{
			unsigned char accNum;
			double depAmt;

			printf("\nPlease enter your account number: ");
			scanf("%hhu", &accNum);
			printf("Please enter the amount you want to deposit: ");
			scanf("%lf", &depAmt);

			deposit(accNum, depAmt);
		}

		// the following is the code snippet if user chooses choice 4
		if (choice == 4)
		{
			unsigned char accNum;
			int pin;
			double wtdAmt;

			printf("\nPlease enter your account number: ");
			scanf("%hhu", &accNum);

			pin = checkPin();

			printf("Please enter the amount you want to withdraw: ");
			scanf("%lf", &wtdAmt);

			withdraw(accNum, pin, wtdAmt);
		}

		// the following is the code snippet if user chooses choice 5
		if (choice == 5)
		{
			dataBase = fopen("bank.csv", "w");
			end(dataBase);
			return 0;
		}
	}
	return 0;
}