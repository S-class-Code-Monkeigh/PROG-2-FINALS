/*note function data types not final, di pa kaayo ko maayos sa file processing*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define dMax 15

#ifndef PDL_h
#define PDL_h

FILE *fptr;
FILE *temp; //for record delete function
FILE *docketptr;
FILE *dtemp;//for docket delete function

typedef struct{
	char city[30];
	int zipCode;
	char province[30];
}address; //city, zipcode, province

typedef struct{
	int day;
	char Month[20];
	int year;
}date;

typedef struct{
	char facilityCode[15]; //prison located combination of letters and numbers
	int pdl_ID; //pdl ID number
	int noCrimes; //number of crimes committed for docket number
	char pdl_name[50]; // pdl name
	address pdl_address; //pdl previous home address
	date date_rendered; //pdl date of capture
	date dateOfBirth; //pdl date of birth
	char sex[7]; //gender
	char status[10];//married/single
}pdl; //person deprived of liberty struct

address getAddress();
date getDate();
pdl getPdl();//get record

//misc functions for ease of use
void menu(); //main menu
char* allCap(char c[]);//capitalizes string
int isdateValid(date);//checks if date entered is valid
int isStatusValid(char c[]);//checks if entered marital status is valid

//seperate function to simplify docket number storage
int getDocketno();//gets information for the docket numbers
void appendDocketNo(int noCrimes, int ID); //adds docket numbers to the .txt file -to be called in addRecord()
void docketNoDisplay(int searchID);//displays docket numbers -to be called in displayRecord()
void deleteDocket(int deleteID); //deletes docket record

//main functions
void displayRecord(pdl r);//displays singular record
void displayAll();//displays all records
void addRecord(); //adds a new record to the text file
void searchRecord();//searches record based off facility code or ID number
void updateRecord();//returns new information for a pdl record
void deleteRecord();/*deletes a record by copies .txt file to another .txt file except for 
	record to be deleted then renames the temp.txt file to the original*/

void inputError(); //for input error message and clearing buffer
void clearInBuff(); //while getchar loop for clearing buffer (ako lng ni gibutang for now but i guess ma gamit rman fflush(stdin) pd)

#endif
