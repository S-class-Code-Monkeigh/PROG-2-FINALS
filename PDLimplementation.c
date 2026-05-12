#include "PDL.h"

address getAddress(){
	address a;
	printf("Enter city: ");
	fgets(a.city, sizeof(a.city), stdin);
	do{
		printf("Enter zipcode (00000): ");
		scanf("%d", &a.zipCode);
	}while(a.zipCode > 99999 || a.zipCode < 10000);
	fflush(stdin);
	printf("Enter province: ");
	fgets(a.province, sizeof(a.province), stdin);
	
	return a;

}
date getDate(){
	date d;
	printf("Month, Day, Year: ");
	scanf("%s%d%d", d.Month, &d.day, &d.year);
	return d;
}
pdl getPdl();

void menu(){
	pdl p;
	int choice;
	printf("Person Deprived of Liberty records");
	printf("1 - Display All Records, 2 - Search for a PDL.");
}
char* allCap(char c[]){
	int size = strlen(c), i;
	for(i = 0; i < size; i++){
		c[i] = toupper(c[i]);
	}
	return c;
}
int isdateValid(date d){
	if(d.day > 31) return 0;
	if(d.day < 0) return 0;
	if(strcmp(allCap(d.Month), "FEBRUARY") == 0){
		if(d.year%4 == 0){
			if(d.day > 29) return 0;
		}
		if(d.day > 28) return 0;
	}
	if(strcmp(allCap(d.Month), "APRIL") == 0) if(d.day > 30) return 0;
	if(strcmp(allCap(d.Month), "JUNE") == 0) if(d.day > 30) return 0;
	if(strcmp(allCap(d.Month), "SEPTEMBER") == 0)if(d.day > 30) return 0;
	if(strcmp(allCap(d.Month), "NOVEMBER") == 0)if(d.day > 30) return 0;
	
	return 1;
}

int isStatusValid(char c[]){
	if(strcmp(allCap(c), "MARRIED") == 0) return 1;
	if(strcmp(allCap(c), "SINGLE")== 0) return 1;
	if(strcmp(allCap(c), "DIVORCED")== 0) return 1;
	if(strcmp(allCap(c), "SEPERATED")== 0) return 1;
	if(strcmp(allCap(c), "WIDOWED")== 0) return 1;
	return 0;
}
void displayRecord(pdl r);//displays singular record;
void displayAll();//displays all records
void searchRecord();//searches record based off facility code

pdl updateRecord();//returns new information for a pdl record
pdl deleteRecord();//deletes an entire record
