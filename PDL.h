/*note function data types not final, di pa kaayo ko maayos sa file processing*/
#include <stdio.h>
#include <stdlib.h>
#incldue <string.h>
#include <ctype.h>

#ifndef PDL_h
#define PDL_h
typedef struct{
	char fName[30];
	char inital;
	char sName[30];
}name;//first name, middle inital, surname

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
	int docketNum[15]; //criminal case, array because may have comitted multiple crimes
	name pdl_name; // pdl name
	address pdl_address; //pdl previous home address
	date date_rendered; //pdl date of capture
	date dateOfBirth; //pdl date of birth
	char sex[7]; //gender
	char status[10];//married/single
}pdl; //person deprived of liberty struct

name getName();
address getAddress();
date getDate();
pdl getPdl();

void menu(); //main menu
void displayRecord(pdl r);//displays singular record;
void displayAll();//displays all records
void searchRecord();//searches record based off facility code
pdl updateRecord();//returns new information for a pdl record
pdl deleteRecord();//deletes an entire record
#endif
