/*note function data types not final, di pa kaayo ko maayos sa file processing*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max 100

#ifndef PDL_h
#define PDL_h

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
	char pdl_name[50]; // pdl name
	address pdl_address; //pdl previous home address
	date date_rendered; //pdl date of capture
	date dateOfBirth; //pdl date of birth
	char sex[7]; //gender
	char status[10];//married/single
}pdl; //person deprived of liberty struct

address getAddress();
date getDate();
pdl getPdl();

void menu(); //main menu
char* allCap(char c[]);//capitalizes string
int isdateValid(date);//checks if date entered is valid

void displayRecord(pdl);//displays singular record; -Kharl
void displayAll();//displays all records - Frenz
void searchRecord();//searches record based off facility code - Matt


int isStatusValid(char c[]);//checks if entered marital status is valid

pdl updateRecord();//returns new information for a pdl record
pdl deleteRecord();//deletes an entire record
#endif
