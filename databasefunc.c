/*****************************************************************
//
// NAME: Angela Zheng
//
// HOMEWORK: Project 1 
//
// CLASS: ICS 212
//
// INSTRUCTOR: Ravi Narayan
//
// DATE: March 12, 2017
//
// FILE: databasefunc.c
//
// DESCRIPTION: Contains all database functions needed for project 1.
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"
#include "db.h"
#include "ui.h"

/*****************************************************************
//
//  Function name:  writefile
//
//  DESCRIPTION:    Writes text files.
//
//  Parameters:     accarray (struct account *)    :  pointer to start of linked list
//                  filename (char [])             :  name of the file to print to
//
****************************************************************/

void writefile(struct record * accarray, char filename[])
{
    FILE * inf;
    struct record * pos = accarray;

    /* DEBUG MODE */
    if (debugmode == 1)
    {
        printf("*** Debug mode\nwritefile: File has been written\n");
        printf("Starting address: %p\nFile name: %s\n*** Debug mode\n\n", (void *)&accarray, filename);
    }
    /* DEBUG MODE */

    inf = fopen(filename, "w"); 
    while(pos != NULL)
    {
        fprintf(inf, "%s\n", (*pos).name); 
        fprintf(inf, "%d\n", (*pos).accountno);
        fprintf(inf, "%s\n\n", (*pos).address);
        pos = (*pos).next;
    }

    if (inf != NULL)
    {
        fclose(inf);
    }
}

/*****************************************************************
//
//  Function name:  readfile
//
//  DESCRIPTION:    Reads accounts in a file and adds them to a linked list
//
//  Parameters:     start (struct account *)   :  start of the linked list
//                  filename (char [])         :  name of the file to print to
//
//  Return values:   -1        :  text file does not exist
//                    0        :  success
//
****************************************************************/

int readfile(struct record ** start, char filename[])
{
     int i, count, retval;
     FILE *inf;
     char name[15], address[80];
     int accountno;
     
     inf = fopen(filename, "r");
 
     if (inf == NULL)
     {
        retval = -1;
     }
     else
     {
         /* DEBUG MODE */

         if (debugmode == 1)
         {
             printf("*** Debug mode\nreadfile: File has been read.\n");
             printf("Starting address: %p\nFile name: %s\n*** Debug mode\n\n", (void *)&(*start), filename); 
         }

         /* DEBUG MODE */

         i = 0;
         retval = 0;

         do
         { 
             switch(i % 4)
             {
                 case 0 :
                     fscanf(inf, " %[^\n]s", name); 
                     break;
               
                 case 1 :
                    fscanf(inf, "%d%*c", &accountno);
                    break;
 
                 case 2 :
                    count = 0;
                    while(count < 80)
                    {
                        address[count] = (char)fgetc(inf);
                        if(address[count] == '\n' && address[count - 1] == '\n')
                        {
                            address[count] = 0;
                            count = 80;
                        }
                        count++;
                    }
                    break;

               case 3 :
		    addRecord(start, accountno, name, address); 
                    break;
              }     
              i++;
          } while (feof(inf) == 0);
          fclose(inf);
     }
     return retval;
}

/*****************************************************************
//
// Function name: addRecord
//
// DESCRIPTION: Adds a record to the database.
//
// Parameters:  start  (struct record **) : Pointer to start of the linked list
//              name    (char [])         : Name of the person
//              acctno  (int)             : Person's account number
//              address (char [])         : Address of the person
//
// Return vales: 0 : success
                 1 : error
//
****************************************************************/
int addRecord(struct record ** start, int acctno, char name [], char address [])
{
    struct record *temp, *temp2;
    int errornum = 0;

    /* DEBUG MODE */

    if (debugmode == 1)
    {
        printf("*** Debug mode -- (addRecord Parameters)\nRecord address: %p", (void *)&start);
        printf("\nAccount number: %d", acctno);
        printf("\nName: %s \nAddress: %s\n*** Debug mode\n\n", name, address);
    }
    /* DEBUG MODE */

    if (acctno < 0 || name == NULL || address == NULL)
    {
        errornum = 1;
    }

    if (*start == NULL)
    {
        *start = (struct record *) malloc(sizeof(struct record));
        (**start).accountno = acctno;
        (**start).next = NULL;
        strcpy((**start).name, name);
        strcpy((**start).address, address);
    }
    else if ((**start).accountno >= acctno)
    {
        temp = *start;
        *start = (struct record *) malloc(sizeof(struct record));
        (**start).next = temp;
        (**start).accountno = acctno;
        strcpy((**start).name, name);
        strcpy((**start).address, address);
    }
    else
    {
        temp = *start;

        while ((*temp).next != NULL && temp != NULL)
        {
            temp2 = NULL;

            if (acctno <= (*(*temp).next).accountno)
            {
                temp2 = (*temp).next;
                (*temp).next = (struct record *) malloc(sizeof(struct record));
                (*(*temp).next).accountno = acctno;
                strcpy((*(*temp).next).address, address);
                strcpy((*(*temp).next).name, name);
                (*(*temp).next).next = temp2;
                
                break;
            }
            temp = (*temp).next;
        }

        if ((*temp).accountno < acctno && (*temp).next == NULL)
        {
            (*temp).next = (struct record *) malloc(sizeof(struct record));
            (*(*temp).next).next = NULL;
            (*(*temp).next).accountno = acctno;
            strcpy((*(*temp).next).name, name);
            strcpy((*(*temp).next).address, address);
        } 
    }
    return errornum;
}
 

/*****************************************************************
//
// Function name: printRecord
//
// DESCRIPTION: Prints a record(s) with the specified account number.
//
// Parameters:  record  (struct record *) : Beginning of the database linked list
//              acctno  (int)             : Person's account number
//
// Return vales:  0 : success
//               -1 : record does not exist
//
****************************************************************/

int printRecord(struct record * start, int acctno)
{
    struct record * temp = start;
    int retval = 0;

    /* DEBUG MODE */

    if (debugmode == 1)
    {
        printf("*** Debug mode --- (printRecord Parameters)\nRecord address: %p \nAccount number: %d\n", (void *)&start, acctno);
        printf("*** Debug mode\n\n");
    }

    /* DEBUG MODE*/ 
 
    if (temp == NULL)
    {
        retval = -1;
    }
    while (temp != NULL)
    { 
        if ((*temp).accountno == acctno)
        {
            printf("Account number: %d\nName: %s\nAddress: %s\n", acctno, (*temp).name, (*temp).address);
        }
        temp = (*temp).next;
    }


    return retval;
}

/*****************************************************************
//
// Function name: modifyRecord
//
// DESCRIPTION: Modifies a record(s) with the specified account number.
//
// Parameters:  record  (struct record *) : The first record in the datbase
//              acctno  (int)             : Person's account number
//              address (char [])         : Person's new address
//
// Return vales: 0 : success
//              -1 : record does not exist
//
****************************************************************/

int modifyRecord (struct record * start, int acctno, char address [])
{
    struct record * temp = start;
    int retval = 0;
 
    /* DEBUG MODE */

    if (debugmode == 1)
    {
        printf("*** Debug Mode --- (modifyRecord Parameters)\nRecord address: %p\nAccount number: %d", (void *)&start, acctno);
        printf("\nAddress: %s\n*** Debug mode\n\n", address);
    }

    /* DEBUG MODE */

    if (temp == NULL)
    {
        retval = -1;
    } 
    while (temp != NULL)
    {
        if ((*temp).accountno == acctno)
        {
            strcpy((*temp).address, address);
        }
        temp = (*temp).next;
    }
    return retval;
}

/*****************************************************************
//
// Function name: printAllRecords
//
// DESCRIPTION: Prints all records in the database.
//
// Parameters:  record  (struct record *) : The first record in the database
//
****************************************************************/

void printAllRecords(struct record * record)
{
    struct record * temp;

    /* DEBUG MODE */
    if (debugmode == 1)
    {
        printf("*** Debug mode --- (printAllRecords Parameter)\nStarting record address: %p\n *** Debug mode\n\n", (void *)&record);
    }
    /* DEBUG MODE */

    temp = record;
 
    while (temp != NULL)
    { 
        printf("Account number: %d\nName: %s\nAddress: %s\n\n", (*temp).accountno, (*temp).name, (*temp).address); 
        temp = (*temp).next;
    } 
}

/*****************************************************************
//
// Function name: deleteRecord
//
// DESCRIPTION: Prints a record with the specified account number.
//
// Parameters:  record  (struct record **): Address of first record
//                                          in the database
//              acctno  (int)             : Person's account number
//
// Return vales: 0 : success
//               1 : invalid account number
//               2 : empty list
//
****************************************************************/

int deleteRecord(struct record ** start, int acctno)
{
    struct record *temp, *temp2, *tempBefore;
    int errornum = 0;

    /* DEBUG MODE */

    if (debugmode == 1)
    {
        printf("*** Debug mode --- (deleteRecord Parameters)\nRecord address: %p", (void *)&start);
        printf("\nAccount number: %d\n*** Debug mode\n\n", acctno);
    }
  
    /* DEBUG MODE */

    if (acctno < 0 || acctno == NULL)
    {
        errornum = 1;
    }

    if (*start == NULL)
    {
        errornum = 2;
    }
    else if (*start != NULL)
    {
        tempBefore = NULL;
        temp = *start;

        while (temp!= NULL)
        {    
            if ((*temp).accountno == acctno)
            {
                if (tempBefore != NULL)
                {
                    temp2 = (*temp).next;
                    free(temp);
                    temp = temp2;
                    (*tempBefore).next = temp2;
                }
                else
                {
                    temp2 = (**start).next;
                    free(*start);
                    temp = temp2;
                    *start = temp2;
                }
            }
            else 
            {
                tempBefore = temp;
                temp = (*temp).next;
            }
        }
    }
    return 0;
}
