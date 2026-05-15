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

int getDocketno(){
	int  d;
	printf("Enter Docket number: ");
	scanf("%d[^\n]", &d);
	return d;
}

void appendDocketNo(int noCrimes){
	int docketNo[15], i;
	
	for(i = 0; i < noCrimes; i++){
		docketNo[i] = getDocketno();
	}
	docketptr = fopen("docketNoRecord.txt", "a");
	if(docketptr == NULL){
		printf("COULD NOT OPEN FILE");
	}
	else{
		for(i = 0; i <noCrimes; i++){
			fprintf(docketptr,"%d ", docketNo[i]);
		}
		fprintf(docketptr,"\n");
	}
	
	fclose(fptr);
}

void docketNoDisplay(int noCrimes, int ID){
	int docketNo[15], i;
	docketptr = fopen("docketNoRecord", "r");
	if(docketptr == NULL){
		printf("COULD NOT OPEN FILE");
	}
	else{
		for(i = 0; i < noCrimes; i++){
			fscanf(docketptr,"%d ", docketNo[i]);
		}
		
	}
}
void menu(){
	pdl r;
	int choice;
    
//    fptr = fopen("pdlRecord.txt", "w");
//    if(fptr == NULL){
//    	printf("File could not be opened "); //creates file
//	}
//	fclose(fptr);
    do {
    	//system("cls");
        printf("\n=== PERSON DEPRIVED OF LIBERTY RECORDS SYSTEM ===\n");
        printf("[1] - Add a Record\n");
        printf("[2] - Search/Find a Record\n");
        printf("[3] - Update/Edit a Record\n");
        printf("[4] - Delete a Record\n");
        printf("[5] - Display All Records\n");
        printf("[6] - Exit\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        fflush(stdin);
        
        switch(choice) {
            case 1:
                addRecord();
                printf("\nRecord added successfully!\n");
                break;
                
            case 2: printf("Search for a record!\n");
            	searchRecord();
                break;
                
            case 3:printf("Update a record!\n");
                break;
                
            case 4:printf("Delete a record!\n");
                break;
                
            case 5:printf("Dispaly all record!\n");
                //displayAll(r);
                break;
                
            case 6:
                printf("Thank you for using PDL Records System!\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
    } while(choice != 6);
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
    printf("\n=== PDL RECORD ===\n");
    printf("Facility Code: %s\n", r.facilityCode);
    printf("PDL ID: %d\n", r.pdl_ID);
    printf("Name: %s\n", r.pdl_name);
    printf("Address: %s, %s %d\n", r.pdl_address.city, r.pdl_address.province, r.pdl_address.zipCode);
    printf("Date Rendered: %s %d, %d\n", r.date_rendered.Month, r.date_rendered.day, r.date_rendered.year);
    printf("Date of Birth: %s %d, %d\n", r.dateOfBirth.Month, r.dateOfBirth.day, r.dateOfBirth.year);
    printf("Sex: %s\n", r.sex);
    printf("Marital Status: %s\n", r.status);
    printf("Crimes: %d\n", r.noCrimes);
    printf("Docket Numbers: ");
    printf("\n");
}

void displayAll(pdl r[]){
	int i;
	for(i = 0; i < max; i++){
		displayRecord(r[i]);
	}
}

void searchRecord(){
	pdl r;
    char searchfCode[15];
    int searchID, choice, searchType, found = 0;
    
    printf("Enter [1] PDL facility code or [2] ID: ");
    scanf("%d", &choice);
    while(getchar() != '\n');
    
    switch(choice){
        case 1: 
            printf("Enter facility code: ");
            fgets(searchfCode, sizeof(searchfCode), stdin);
            searchfCode[strcspn(searchfCode, "\n")] = 0;
            searchType = 1;
            break;
        case 2: 
            printf("Enter PDL ID: ");
            scanf("%d", &searchID);
            searchType = 2;
            while(getchar() != '\n');
            break;
        default:
            printf("Invalid choice!\n");
            return;
    }

    FILE *fptr = fopen("pdlRecord.txt", "r");
    if(fptr == NULL){
        printf("Failed to open file!\n");
        return;
    }
    
    while(fscanf(fptr, "%s %d %d %[^\n] %s %d %s %s %d %d %s %d %d %s %s",
                 r.facilityCode, &r.pdl_ID, &r.noCrimes, r.pdl_name, 
                 r.pdl_address.city, &r.pdl_address.zipCode, r.pdl_address.province,
                 r.date_rendered.Month, &r.date_rendered.day, &r.date_rendered.year,
                 r.dateOfBirth.Month, &r.dateOfBirth.day, &r.dateOfBirth.year,
                 r.sex, r.status) == 15){
        
        if(searchType == 1 && strcmp(searchfCode, r.facilityCode) == 0){
            displayRecord(r);
            found = 1;
        }
        else if(searchType == 2 && searchID == r.pdl_ID){
            displayRecord(r);
            found = 1;
        }
    }
    
    if(!found){
        printf("RECORD NOT FOUND\n");
    }
    fclose(fptr);
}

void addRecord()
{

	    pdl r;
    char choice;
    
    do{
        r = getPdl();
        
        FILE *fptr = fopen("pdlRecord.txt", "a");
        if(fptr == NULL){
            printf("File Failed to Open!\n");
            return;
        }
        
        fprintf(fptr, "%s %d %d %s %s %d %s %s %d %d %s %d %d %s %s\n", 
                r.facilityCode, r.pdl_ID, r.noCrimes, r.pdl_name, 
                r.pdl_address.city, r.pdl_address.zipCode, r.pdl_address.province,
                r.date_rendered.Month, r.date_rendered.day, r.date_rendered.year,
                r.dateOfBirth.Month, r.dateOfBirth.day, r.dateOfBirth.year,
                r.sex, r.status);
        fclose(fptr);
        
        printf("\nAdd another record? (y/n): ");
        scanf(" %c", &choice);
        while(getchar() != '\n');
        
    }while(choice == 'y' || choice == 'Y');
	
}
void updateRecord(){
	
}
void deleteRecord();

/*addRecord(): 	
	pdl r;
	int quit = 0;
	do
	{
		fflush(stdin);
		
		fptr = fopen("pdlRecord.txt", "a");
		if(fptr == NULL){
			printf("File Failed to Open!");
		}
	else{
		r = getPdl();
		fprintf(fptr,"%s. %d. %d. %s. %s. %d. %s. %s. %d. %d. %s. %d. %d. %s. %s\n", 
		r.facilityCode, r.pdl_ID, r.noCrimes, r.pdl_name, r.pdl_address.city, r.pdl_address.zipCode, r.pdl_address.province, 
		r.date_rendered.Month, r.date_rendered.day, r.date_rendered.year, r.dateOfBirth.Month, r.dateOfBirth.day, 
		r.dateOfBirth.year, r.sex, r.status);
		fclose(fptr);
		
		printf("Press [1] - quit");
		scanf("%d", &quit);
	}

		
	}while(quit != 1);
	*/
