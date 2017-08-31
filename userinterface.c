/*****************************************************************
//
// NAME: Angela Zheng
//
// HOMEWORK: Project1 
//
// CLASS: ICS 212
//
// INSTRUCTOR: Ravi Narayan
//
// DATE: March 12, 2017
//
// FILE: userinterface.c 
//
// DESCRIPTION: This file contains a user interface that communicates
// with the user and accesses functions to interact with a database
//
****************************************************************/

#include <stdio.h>
#include "record.h"
#include "db.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void getaddress(char [], int);
void menu();

int debugmode;

/*****************************************************************
//
// Function name: main
//
// DESCRIPTION: A user interface that communicates with a user and
// allows them to access functions that add, delete, modify, and
// print records. If the user puts spaces in their account number,
// only the numbers appearing before the spaces will be stored.
//
// NOTE: Account numbers must be 10 characters or less.
//
// Parameters:  argc    ints passed in via command line.
//              argv    parameters passed in via command line.
//
// Return vales: 0 : success
//
****************************************************************/

int main(int argc, char * argv[])
{
    struct record * start;
    int cont;
    char numAcctno[80], name[25], address[80], rawCommand[50];
    int command, acctnum;
    int checking, pos, trailingcharacter, repeat;

    debugmode = 0;
    start = NULL;
    cont = 1;
    checking = 0;
    pos = 0;    
    trailingcharacter = 0;
    repeat = 0;

    /* Checking for debugmode. */

    if (argc == 1)
    {
        debugmode = 0;
    }
    else
    {
        if (strcmp(argv[1], "debug") == 0)
        {
            debugmode = 1;
        }
        else
        {
            printf("hw3: Insufficient arguments.\n");
            printf("Usage: hw3\n");
            printf("       hw3 [-p]\n");
            cont = 0;
        }
    }

    if (cont == 1)
    {
        printf(" _  _  _ _______        _______  _____  _______ _______");
        printf("\n |  |  | |_____");
        printf("_ |      |       |     | |  |  | |______");
        printf("\n |__|__| |______ |_____ |_____  |_____| |");
        printf("  |  | |______\n\n");
        readfile(&start, "dump.txt");
    }

    while (cont == 1)
    {
       menu();

       repeat = 0;

       do
       {
           trailingcharacter = 0;
           fgets(rawCommand, 10, stdin);

           if (rawCommand[0] == '\n')
           {
               while (pos < strlen(rawCommand))
               {
                   /* Clear out the buffer. */

                   rawCommand[pos] = rawCommand[pos + 1];
                   pos++;
               }

               trailingcharacter = 1;
           }
           command = atoi(rawCommand);

           if (command == 0 && trailingcharacter == 0)
           {
               printf("\n\n================================================================\n");
               printf("||                  Error: invalid command.                   ||\n");
               printf("================================================================\n");

           }
        } while (command == 0);

        if (command == 0)
        {
            printf("\n\n================================================================\n");
            printf("||                  Error: invalid command.                   ||\n");
            printf("================================================================\n");

        }
        else if (command == 1)
        {
           /* Add a new record. */

            repeat = 0;

            do
            {
                if (repeat == 0)
                {
                printf("\n\n================================================================\n");
                printf("||   Please enter the account number of the record to add     ||\n");
                printf("||                      without spaces.                       ||\n");
                printf("||    Account numbers must consist of only integers and be    ||\n");
                printf("||                       10 digits or less.                   ||\n");
                printf("================================================================\n");

                }
                else
                {
                    printf("\n\n================================================================\n");
                    printf("||              Error: invalid account number                 ||\n");
                    printf("================================================================\n");

                    printf("\n\n================================================================\n");
                    printf("||      Please input an account number without spaces.        ||\n");
                    printf("||    Account numbers must consist of only integers and be    ||\n");
                    printf("||                       10 digits or less.                   ||\n");
                    printf("================================================================\n");

                }

                fgets(numAcctno, 70, stdin);

                if (strlen(numAcctno) > 10)
                {
                    repeat = 1;
                }
                else
                {
                    repeat = 0;
                }

                acctnum = atoi(numAcctno);
            }
            while (acctnum == 0 || repeat == 1);

            printf("\n\n================================================================\n");
            printf("||    Please input a name, pressing enter when you are done.    ||\n");
            printf("================================================================\n");
            fgets(name, 23, stdin);

            name[strlen(name) - 1] = '\0';
            printf("\n");
            
            printf("\n\n================================================================\n");
            printf("|| Please enter an address. Type '-.' without quotation marks   ||\n");
            printf("||   and then press enter to indicate you are finished typing.  ||\n");
            printf("================================================================\n");
            getaddress(address, 80);
 
            addRecord(&start, acctnum, name, address);

            printf("\n\n================================================================\n");
            printf("||                 Record successfully added                  ||\n");
            printf("================================================================\n");

        }
        else if (command == 2)
        {
            /* Modify a record. */

            do
            {
                if (repeat == 1)
                {
                    printf("\n\n================================================================\n");
                    printf("||              Error: invalid account number                 ||\n");
                    printf("================================================================\n");
                }

                printf("\n\n================================================================\n");
                printf("||      Please input the account number of the record to      ||\n");
                printf("||                  modify without spaces.                    ||\n");
                printf("||    Account numbers must consist of only integers and be    ||\n");
                printf("||                       10 digits or less.                   ||\n");
                printf("================================================================\n");

                fgets(numAcctno, 70, stdin);

                if (strlen(numAcctno) > 10)
                {
                    repeat = 1;
                }
                else
                {
                    repeat = 0;
                }

                acctnum = atoi(numAcctno);
            }
            while (acctnum == 0 || repeat == 1);
            
            printf("\n\n================================================================\n");
            printf("|| Please enter an address. Type '-.' without quotation marks   ||\n");
            printf("||   and then press enter to indicate you are finished typing.  ||\n");
            printf("================================================================\n");
            getaddress(address, 80);

            if(modifyRecord(start, acctnum, address) == -1)
            {
                printf("\n\n================================================================\n");
                printf("||        Error: no account exists with that number           ||\n");
                printf("================================================================\n");
            }
            else
            {
                printf("\n\n================================================================\n");
                printf("||             Record(s) successfully modified                ||\n");
                printf("================================================================\n");
            }
        }
        else if (command == 3)
        {
            /* Print out a specific record. */

            do
            {
                if (repeat == 1)
                {
                    printf("\n\n================================================================\n");
                    printf("||              Error: invalid account number                 ||\n");
                    printf("================================================================\n");
                }


                printf("\n\n================================================================\n");
                printf("||   Please input the account number of the record to print   ||\n");
                printf("||                       without spaces.                      ||\n");
                printf("||    Account numbers must consist of only integers and be    ||\n");
                printf("||                       10 digits or less.                   ||\n");
                printf("================================================================\n");

                fgets(numAcctno, 70, stdin);

                if (strlen(numAcctno) > 10)
                {
                    repeat = 1;
                }
                else
                {
                    repeat = 0;
                }

                acctnum = atoi(numAcctno);
            }
            while (acctnum == 0 || repeat == 1);

            if(printRecord(start, acctnum) == -1)
            {
                printf("\n\n================================================================\n");
                printf("||        Error: no account exists with that number           ||\n");
                printf("================================================================\n");
            }
        }
        else if (command == 4)
        {
            printf("\n\n================================================================\n");
            printf("||             Printing all available records...              ||\n");
            printf("================================================================\n");
            printAllRecords(start);
        }
        else if (command == 5)
        {

            do
            {
                if (repeat == 1)
                {
                    printf("\n\n================================================================\n");
                    printf("||              Error: invalid account number                 ||\n");
                    printf("================================================================\n");
                }

                printf("\n\n================================================================\n");
                printf("|| Please enter the account number of the record(s) to delete ||\n");
                printf("||                      without spaces.                       ||\n");
                printf("||    Account numbers must consist of only integers and be    ||\n");
                printf("||                       10 digits or less.                   ||\n");
                printf("================================================================\n");

                fgets(numAcctno, 70, stdin);

                if (strlen(numAcctno) > 10)
                {
                    repeat = 1;
                }
                else
                {
                    repeat = 0;
                }

                acctnum = atoi(numAcctno);
            }
            while (acctnum == 0 || repeat == 1);

            if (deleteRecord(&start, acctnum) == 0)
            {
                printf("\n\n================================================================\n");
                printf("||                 Deletion(s) successful                     ||\n");
                printf("================================================================\n");
            }
            else 
            {
                printf("\n\n================================================================\n");
                printf("||        Error: no account exists with that number           ||\n");
                printf("================================================================\n");
            }

        }
        else if (command == 6)
        {
            printf("\n\n================================================================");
            printf("\n||   Type (1) to confirm your exit or any letter followed by  ||\n");
            printf("||          entering if you would like to continue.           ||\n");
            printf("================================================================\n");
            scanf("%s", rawCommand);
            command = atoi(rawCommand);

            printf("\n");

            if (command == 1)
            {
                cont = 0;
            }
            else
            {
                cont = 1;
            }
        }
    }
    writefile(start, "dump.txt");
    return 0;
}


/*****************************************************************
//
// Function name: menu
//
// DESCRIPTION: Prints a menu and all the options available in the
// user interface.
//
****************************************************************/

void menu()
{
    printf("\n\n================================================================");
    printf("\n||    Please type the number next to your desired command.     || \n");
    printf("================================================================ \n");

    printf("|| (1) Add a new record   || (2) Modify a record               || \n");
    printf("|| (3) Print out a record || (4) Print all stored information. || \n");
    printf("|| (5) Delete a record    || (6) Quit                          || \n");

    printf("=============================================================== \n \n");
}

/*****************************************************************
//
// Function name: getaddress
//
// DESCRIPTION: Receives and stores a user inputted address.
//
// Parameters:  address (char []) : pointer to the array that holds the address
//              size    (int)     : size of the array that holds the address
//
****************************************************************/

void getaddress(char address [], int size)
{
    int startExit = 0;
    int trueExit = 0;
    char input;
    int pos = 0;

    while(trueExit == 0 && pos < size)
    {
        input = fgetc(stdin);

        if (input == '-')
        {
            startExit = 1;
            address[pos] = input;
            pos++;
        }
        else if (input == '.')
        {
            if (startExit == 1)
            {

                /* Removes extra '\n' at the end. */

                trueExit = 1;
                address[pos - 1] = '\0';
            }
            else
            {
                address[pos] = input;
                pos++;
            }
        }
        else
        {
            address[pos] = input;
            pos++;
        }
    }
    address[pos] = '\0';

    printf("\n");
}
