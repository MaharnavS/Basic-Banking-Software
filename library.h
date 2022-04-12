#ifndef __LIBRARY_H
#define __LIBRARY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Account *account;
typedef account* acc_list;

struct Account
{
    char name[51];
    unsigned char acc_no;
    int PIN;
    double balance;
};

void init(FILE *csv_file_ptr_in_read_mode);

unsigned char new_account(char name[51],int pin);
void display_balance(unsigned char acccount_number, int pin);
void deposit(unsigned char acccount_number, double amount);
void withdraw(unsigned char acccount_number, int pin, double amount);

void end(FILE *csv_file_ptr_in_write_mode);

#endif // __LIBRARY_H