#include "PDL.h"

<<<<<<< Updated upstream
address getAddress();
date getDate();
pdl getPdl();
=======
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
	printf("Enter Valid Month, Day, Year: ");
	scanf("%s%d%d", d.Month, &d.day, &d.year);
	return d;
}
//	char facilityCode[15]; //prison located combination of letters and numbers
//	int pdl_ID; //pdl ID number
//	int docketNum[15]; //criminal case, array because may have comitted multiple crimes
//	char pdl_name[50]; // pdl name
//	address pdl_address; //pdl previous home address
//	date date_rendered; //pdl date of capture
//	date dateOfBirth; //pdl date of birth
//	char sex[7]; //gender
//	char status[10];//married/single
pdl getPdl(){
	pdl p;
	int crimes = 0, i;
	printf("Enter Facility Code: ");
	fgets(p.facilityCode, sizeof(p.facilityCode), stdin);
	printf("Enter ID number: ");
	scanf("%d", &p.pdl_ID);
	printf("Crimes Committed: ");
	scanf("%d", &crimes);
	for(i = 0; i < crimes; i++){
		printf("Enter docket Num: ");
		scanf("%d", &p.docketNum[i]);
	}
	p.pdl_address = getAddress();
	do{
		printf("Enter Address before incarceration:\n");
		p.date_rendered = getDate();
	}while(isdateValid(p.date_rendered) != 1);
	
	do{
		printf("Enter Date of Birth:\n");
		p.date_rendered = getDate();
	}while(isdateValid(p.date_rendered) != 1);
	fflush(stdin);
	printf("Enter Sex: ");
	fgets(p.sex, sizeof(p.sex), stdin);
	do{
		
	}
	
}
>>>>>>> Stashed changes

void menu(){
	printf("Hello there stewie!\n)");
	printf("Hello there peter!");
    printf("Hello there louise!");
	printf("Hello Notpad++");
}

void displayRecord(pdl r);//displays singular record;
void displayAll();//displays all records
void searchRecord();//searches record based off facility code
pdl updateRecord();//returns new information for a pdl record
pdl deleteRecord();//deletes an entire record
