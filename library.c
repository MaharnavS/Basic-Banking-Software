#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

account accounts_list[256];
int no_of_accounts = 0;

void init(FILE *fp)
{
    if (!fp)
    {
        fclose(fp);
        return;
    }

    char temp, temp_str[451];

    fscanf(fp, "%d", &no_of_accounts);
    fscanf(fp, "%s", temp_str);
    fscanf(fp, "%c", &temp);

    for (int a = 0; a < no_of_accounts; a++)
    {
        account new = (account)malloc(sizeof(struct Account));
        char name_[51]={0};

        for (int i = 0; i < 50; i++)
        {
            char c;
            fscanf(fp, "%c", &c);
            if (c == ',')
                break;
            else
                name_[i] = c;
        }
        strcpy(new->name, name_);

        fscanf(fp, "%hhu", &(new->acc_no));
        fscanf(fp, "%c", &temp);
        fscanf(fp, "%d", &(new->PIN));
        fscanf(fp, "%c", &temp);
        fscanf(fp, "%lf", &(new->balance));
        fscanf(fp, "%c", &temp);

        accounts_list[a] = new;
    }

    fclose(fp);
}

unsigned char new_account(char new_name[51], int pin)
{

    account new = (account)malloc(sizeof(struct Account));

    strcpy(new->name, new_name);
    new->acc_no = no_of_accounts;
    new->PIN = pin;
    new->balance = 100.00;

    accounts_list[no_of_accounts] = new;

    ++no_of_accounts;

    return new->acc_no;
}

void display_balance(unsigned char acccount_number, int pin)
{
    for (int i = 0; i < no_of_accounts; i++)
    {
        if (accounts_list[i]->acc_no == acccount_number)
        {
            if (accounts_list[i]->PIN == pin)
            {
                printf("\nYour account information is as follows:\n"); // Current Balance, Acc No, Name
                printf("\t\tAccount number: %hhu\n", accounts_list[i]->acc_no);
                printf("\t\tName: %s\n", accounts_list[i]->name);
                printf("\t\tBalance: %lf\n", accounts_list[i]->balance);
                return;
            }
            else
            {
                printf("\nThere seems to be an error, please check the entered PIN or account number and try again.\n"); 
                return;
            }
        }
    }
    printf("\nWe couldn't find an account with than number in our database.\nEither check the entered account number and try again.\n(Tip: You can also create a new account with us)\n");
}

void deposit(unsigned char acccount_number, double amount)
{
    if (amount < 0)
    {
        printf("\nThere seems to an error, please check the entered value and try again.\n(Tip: You cannot deposit an amount of less than 0)\n");
        return;
    }

    for (int i = 0; i < no_of_accounts; i++)
    {
        if (accounts_list[i]->acc_no == acccount_number)
        {
            accounts_list[i]->balance += amount;
            printf("\nThanks for your request, the transaction has been executed successfully.\n"); 
            return;
        }
    }
    printf("\nWe couldn't find an account with that number in our database.\nCheck the entered account number and try again.\n(Tip: You can also create a new account with us)\n");
}

void withdraw(unsigned char acccount_number, int pin, double amount)
{
    if (amount < 0)
    {
        printf("\nThere seems to an error, please check the entered value and try again.\n(Tip: You cannot withdraw an amount of less than 0)\n");
        return;
    }

    for (int i = 0; i < no_of_accounts; i++)
    {
        if (accounts_list[i]->acc_no == acccount_number)
        {
            if (accounts_list[i]->PIN == pin)
            {
                if (amount > accounts_list[i]->balance)
                {
                    printf("\nThere seems to be an error, the entered amount is greater than your current balance. Please try again.\n");
                }
                accounts_list[i]->balance -= amount;
                printf("\nYour Updated Account Information is as Follows:\n"); // Current Balance, Acc No, Name
                printf("\t\tAccount Number: %hhu\n", accounts_list[i]->acc_no);
                printf("\t\tName: %s\n", accounts_list[i]->name);
                printf("\t\tAccount Balance: %lf\n", accounts_list[i]->balance);
                return;
            }
            else
            {
                printf("\nThere seems to be an error, please check the entered PIN or account number and try again.\n"); 
                return;
            }
        }
    }
    printf("\nWe couldn't find an account with that number in our database.\nCheck the entered account number and try again.\n(Tip: You can also create a new account with us)\n");
}

void end(FILE *fp)
{
    fprintf(fp, "%d\n", no_of_accounts);
    fprintf(fp, "name,accountNumber,PIN,balance\n");

    for (int a = 0; a < no_of_accounts; a++)
    {
        account record = accounts_list[a];
        fprintf(fp, "%s", record->name);
        fprintf(fp, ",");
        fprintf(fp, "%hhu", record->acc_no);
        fprintf(fp, ",");
        fprintf(fp, "%d", record->PIN);
        fprintf(fp, ",");
        fprintf(fp, "%lf", record->balance);
        fprintf(fp, "\n");
    }
    printf("\nBalance has been updated successfully. Thanks for choosing The Bank, have a nice day.\n");
    fclose(fp);
}