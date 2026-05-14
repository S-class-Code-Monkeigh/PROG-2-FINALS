#include "PDL.h"

address getAddress(){
	address a;
	printf("Enter city: ");
	fgets(a.city, sizeof(a.city), stdin);
	fflush(stdin);
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
	printf("Enter Valid Month, Day, Year: ");
	scanf("%s%d%d", d.Month, &d.day, &d.year);
	return d;
}

pdl getPdl(){
	pdl p;
	int i;
	printf("Enter Facility Code: ");
	fgets(p.facilityCode, sizeof(p.facilityCode), stdin);
	fflush(stdin);
	
	printf("Enter ID number: ");
	scanf("%d", &p.pdl_ID);
	fflush(stdin);
	
	printf("Number Crimes Committed: ");
	scanf("%d", &p.noCrimes);
	fflush(stdin);
	
	for(i = 0; i < p.noCrimes; i++){
		printf("Enter docket Num: ");
		scanf("%d", &p.docketNum[i]);
	}
	fflush(stdin);
	
	printf("Enter PDL name: ");
	fgets(p.pdl_name, sizeof(p.pdl_name), stdin);
	fflush(stdin);
	
	printf("Enter Address before incarceration:\n");
	p.pdl_address = getAddress();
	fflush(stdin);
	
	do{
		printf("Enter Date rendered:\n");
		p.date_rendered = getDate();
	}while(isdateValid(p.date_rendered) != 1);
	fflush(stdin);
	
	do{
		printf("Enter Date of Birth:\n");
		p.dateOfBirth = getDate();
	}while(isdateValid(p.dateOfBirth) != 1);
	fflush(stdin);
	
	printf("Enter Sex: ");
	fgets(p.sex, sizeof(p.sex), stdin);
	fflush(stdin);
	
	do{
		printf("Enter Marital Status: ");
		fgets(p.status, sizeof(p.status), stdin);
	}while(isStatusValid(p.status) == 0);
	
	return p;
}

void menu(){
	pdl p;
	int choice;
	printf("Person Deprived of Liberty records");
	printf("[1] - Display All Records, [2] - Search for a PDL, [3] - Add a record");
	//switch(choice);
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

	if(strcmp(allCap(c), "MARRIED\n") == 0) return 1;
	if(strcmp(allCap(c), "SINGLE\n") == 0) return 1;
	if(strcmp(allCap(c), "DIVORCED\n")== 0) return 1;
	if(strcmp(allCap(c), "SEPERATED\n")== 0) return 1;
	if(strcmp(allCap(c), "WIDOWED\n")== 0) return 1;
	
	else return 0;
}
void displayRecord(pdl r){
	printf("wapakoy sulod");
}//displays singular record;
void displayAll(pdl r[]){
	int i;
	for(i = 0; i < max; i++){
		displayRecord(r[i]);
	}
}//displays all records

pdl* searchRecord(pdl r);//searches record based off facility code

//	char facilityCode[15]; //prison located combination of letters and numbers
//	int pdl_ID; //pdl ID number
//  int noCrimes; //number of crimes committed for docket number
//	int docketNum[15]; //criminal case, array because may have comitted multiple crimes
//	char pdl_name[50]; // pdl name
//	address pdl_address; //pdl previous home address
//	date date_rendered; //pdl date of capture
//	date dateOfBirth; //pdl date of birth
//	char sex[7]; //gender
//	char status[10];//married/single

void getRecord()
{
	pdl r;
	int quit = 0;
	do
	{
		fflush(stdin);
		
		fptr = fopen("pdlRecord.txt", "a");
		if(fptr == NULL){
			printf("File Failed to Open!");
		}

		r = getPdl();
		fprintf(fptr, "%s\t %d\t %d\t %s\t %s\t %d\t %s\t %s\t %d\t %d\t %s\t %d\t %d\t %s\t %s\n", 
		r.facilityCode, r.pdl_ID, r.noCrimes, r.pdl_name, r.pdl_address.city, r.pdl_address.zipCode, r.pdl_address.province, 
		r.date_rendered.Month, r.date_rendered.day, r.date_rendered.year, r.dateOfBirth.Month, r.dateOfBirth.day, 
		r.dateOfBirth.year, r.sex, r.status);
		fclose(fptr);
		
		printf("Press [1] - quit");
		scanf("%d", &quit);
		
	}while(quit != 1);
	
	
}
pdl updateRecord(pdl r);//returns new information for a pdl record
pdl deleteRecord(pdl r);//deletes an entire record
