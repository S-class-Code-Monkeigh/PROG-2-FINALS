#include "PDL.h"

FILE *fptr;
FILE *temp; //for record delete function
FILE *docketptr;
FILE *dtemp;//for docket delete function

address getAddress(){
	address a;
	printf("\tEnter CITY: ");
	fgets(a.city, sizeof(a.city), stdin);
	a.city[strcspn(a.city, "\n")] = '\0'; //removes\n (helps with formatting) by going to the index with "\n" and replacing it with \0
	
	while(1)
	{
		printf("\tEnter ZIPCODE (0000): ");
		if(scanf("%d", &a.zipCode)!=1 || a.zipCode > 9999 || a.zipCode < 1000)
		{
			inputError();
			continue;
		}
		clearInBuff();
		break;
	}

	printf("\tEnter PROVINCE: ");
	fgets(a.province, sizeof(a.province), stdin);
	a.province[strcspn(a.province, "\n")] = '\0';
	return a;
}
date getDate(){
	date d;
	printf("\tMONTH: ");
	fgets(d.Month, sizeof(d.Month), stdin);
	d.Month[strcspn(d.Month, "\n")] = '\0';
	
	printf("\tDAY: ");
	scanf("%d", &d.day);
	clearInBuff();
	
	printf("\tYEAR: ");
	scanf("%d", &d.year);
	clearInBuff();
	
	return d;
}

pdl getPdl(){
	pdl p;
	int i; //wait asa ni gamiton actually WYAHAHA
	printf("=== NEW RECORD ===\n\n");
	printf("Enter FACILITY CODE: ");
	fgets(p.facilityCode, sizeof(p.facilityCode), stdin);
	p.facilityCode[strcspn(p.facilityCode, "\n")] = '\0';
	
	while(1)
	{
		printf("Enter ID number: ");
		if(scanf("%d", &p.pdl_ID)!=1)
		{
			inputError();
			continue;
		}
		clearInBuff();
		break;
	}
	
	while(1)
	{
		printf("Number of CRIMES COMMITTED: ");
		if(scanf("%d", &p.noCrimes)!=1)
		{
			inputError();
			continue;
		}
		clearInBuff();
		break;
	}
	
	printf("Enter PDL NAME: ");
	fgets(p.pdl_name, sizeof(p.pdl_name), stdin);
	p.pdl_name[strcspn(p.pdl_name, "\n")]='\0'; 
	
	printf("ADDRESS PRIOR TO INCARCERATION\n");
	p.pdl_address = getAddress();
	
	do
	{
		printf("DATE RENDERED\n");
		p.date_rendered = getDate();
	}
	while(isdateValid(p.date_rendered) != 1);
	clearInBuff();
	
	do
	{
		printf("DATE OF BIRTH\n");
		p.dateOfBirth = getDate();
	}
	while(isdateValid(p.dateOfBirth) != 1);
	clearInBuff();
	
	printf("Enter SEX: ");
	fgets(p.sex, sizeof(p.sex), stdin);
	p.sex[strcspn(p.sex, "\n")] ='\0';
	
	do{
		printf("Enter MARITAL STATUS: ");
		fgets(p.status, sizeof(p.status), stdin);
		p.status[strcspn(p.status, "\n")] = '\0';
		
	}while(isStatusValid(p.status) == 0);
	
	return p;
}

int getDocketno(){
	int  d;
	printf("Enter Docket number: ");
	scanf("%d[^\n]", &d);
	return d;
}

void appendDocketNo(int noCrimes, int ID){
	int docketNo[dMax], i;
    docketptr = fopen("docketNoRecord.txt", "a");
    
    if (docketptr == NULL) {
        printf("Could not open docket file!\n");
        return;
    }
    
    for (i = 0; i < noCrimes; i++) {
        docketNo[i] = getDocketno();
    }
    
    fprintf(docketptr, "%d %d", ID, noCrimes);
    for (i = 0; i < noCrimes; i++) {
        fprintf(docketptr, " %d", docketNo[i]);
    }
    fprintf(docketptr, "\n"); 
    
    fclose(docketptr);
}

void docketNoDisplay(int searchID){
	int id, noCrimes, docket, i;
    docketptr = fopen("docketNoRecord.txt", "r");
    
    if (docketptr == NULL) {
    	printf("Could not display docket record!");
        return; 
    }
    
    while (fscanf(docketptr, "%d %d", &id, &noCrimes) == 2) {
        if (id == searchID) {
            printf(" DOCKET NUMBERS\n");
            for (i = 0; i < noCrimes; i++) {
                fscanf(docketptr, "%d", &docket);
                printf("\tDocket No. %d: %d\n", i + 1, docket);
            }
            printf("\n");
            fclose(docketptr);
            return; 
        } else {
            for (i = 0; i < noCrimes; i++) {
                fscanf(docketptr, "%d", &docket); 
            }
        }
    }
    fclose(docketptr);
}

void deleteDocket(int deleteID){
	int noCrimes, id, i;
	int docket[dMax];
    docketptr = fopen("docketNoRecord.txt", "r");
    dtemp = fopen("tempdocket.txt", "w");

    if (docketptr == NULL) {
    	printf("Could not display docket record!\n");
        return; 
    }
    if (dtemp == NULL) {
        printf("Failed to create temporary docket file!\n");
        fclose(docketptr);
        return;
    }
    
    while (fscanf(docketptr, "%d %d", &id, &noCrimes) == 2) {
        if (id == deleteID) {
            for (i = 0; i < noCrimes; i++) {
                fscanf(docketptr, "%d", &docket[i]);
            }
        } else {
            fprintf(dtemp, "%d %d", id, noCrimes);
            for (i = 0; i < noCrimes; i++) {
                fscanf(docketptr, "%d", &docket[i]);
                fprintf(dtemp, " %d", docket);
            }
            fprintf(dtemp, "\n");
        }
    }
    
    fclose(docketptr);
    fclose(dtemp);
    
    remove("docketNoRecord.txt");
    rename("tempdocket.txt", "docketNoRecord.txt");
	
}
void menu(){
	pdl r;
	int choice;

    do 
	{
    	printf("============================================================");
        printf("\n\n          PERSON DEPRIVED OF LIBERTY RECORDS SYSTEM          \n\n");
		printf("============================================================\n\n");
        printf("\t[1] - Add a Record\n");
        printf("\t[2] - Search/Find a Record\n");
        printf("\t[3] - Update/Edit a Record\n");
        printf("\t[4] - Delete a Record\n");
        printf("\t[5] - Display All Records\n");
        printf("\t[6] - Exit\n");
        printf("\n\tEnter your choice (1-6): ");
        
		scanf("%d", &choice);
        
		clearInBuff();
        
		
        switch(choice) 
		{
            case 1:
				system("cls");
                addRecord();
                printf("Record added successfully!\n\n");
                break;
                
            case 2: 
				system("cls");
				printf("Search for a record!\n\n");
            	searchRecord();
                break;
                
            case 3:
				updateRecord();
				printf("Updated a record!\n");
                break;
                
            case 4:
				printf("Delete a record!\n");
            	deleteRecord();
                break;
                
            case 5:
                displayAll(r);
                break;
                
            case 6:
                printf("Thank you for using PDL Records System!\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n\n");
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
	
	if(d.day < 1 || d.day > 31)
	{
		printf("ERROR: DAY must be between 1 and 31\n");
		return 0;
	}
	
	char monthUpper[20];
	strcpy(monthUpper, d.Month);
	allCap(monthUpper);
	
	int daysInMonth;
	
	if(strcmp(monthUpper, "JANUARY") == 0)
	{
		daysInMonth = 31;
	}
	else if(strcmp(monthUpper, "FEBRUARY") == 0)
	{
		int isLeapYear = 0;
		if(d.year % 4 == 0)
		{
			if(d.year % 100 == 0)
			{
				if(d.year % 400 == 0)
				{
					isLeapYear = 1;
				}
				else
				{
					isLeapYear = 0;
				}
			}
			else
			{
				isLeapYear = 1;  // Divisible by 4 but not 100 = leap year
			}
		}
		
		daysInMonth = isLeapYear ? 29 : 28;
	}
	else if(strcmp(monthUpper, "MARCH") == 0)
	{
		daysInMonth = 31;
	}
	else if(strcmp(monthUpper, "APRIL") == 0)
	{
		daysInMonth = 30;
	}
	else if(strcmp(monthUpper, "MAY") == 0)
	{
		daysInMonth = 31;
	}
	else if(strcmp(monthUpper, "JUNE") == 0)
	{
		daysInMonth = 30;
	}
	else if(strcmp(monthUpper, "JULY") == 0)
	{
		daysInMonth = 31;
	}
	else if(strcmp(monthUpper, "AUGUST") == 0)
	{
		daysInMonth = 31;
	}
	else if(strcmp(monthUpper, "SEPTEMBER") == 0)
	{
		daysInMonth = 30;
	}
	else if(strcmp(monthUpper, "OCTOBER") == 0)
	{
		daysInMonth = 31;
	}
	else if(strcmp(monthUpper, "NOVEMBER") == 0)
	{
		daysInMonth = 30;
	}
	else if(strcmp(monthUpper, "DECEMBER") == 0)
	{
		daysInMonth = 31;
	}
	else
	{
		printf("Invalid MONTH input. Please try again.\n");
		return 0;
	}
	
	if(d.day > daysInMonth)
	{
		printf("Invalid DAY input. Please try again.");
		return 0;
	}
	
	return 1;
}

int isStatusValid(char c[])
{
	char *validStatus[] = {"MARRIED", "SINGLE", "DIVORCED", "SEPARATED", "WIDOWED"};
	int numStatus = 5;
	
	char statusUpper[10];
	strcpy(statusUpper, c);
	allCap(statusUpper);
	
	for(int i = 0; i < numStatus; i++)
	{
		if(strcmp(statusUpper, validStatus[i]) == 0)
		{
			return 1;
		}
	}
	
	printf("Invalid STATUS input. Please try again.\n");
	return 0;
}

void displayRecord(pdl r){
    printf("\n=== PDL RECORD ===\n\n");
    printf(" Facility Code: %s\n", r.facilityCode);
    printf(" PDL ID: %d\n", r.pdl_ID);
    printf(" Name: %s\n", r.pdl_name);
    printf(" Address: %s, %s %d\n", r.pdl_address.city, r.pdl_address.province, r.pdl_address.zipCode);
    printf(" Date Rendered: %s %d, %d\n", r.date_rendered.Month, r.date_rendered.day, r.date_rendered.year);
    printf(" Date of Birth: %s %d, %d\n", r.dateOfBirth.Month, r.dateOfBirth.day, r.dateOfBirth.year);
    printf(" Sex: %s\n", r.sex);
    printf(" Marital Status: %s\n", r.status);
    printf(" Crimes: %d\n", r.noCrimes);
    docketNoDisplay(r.pdl_ID);
    printf("\n");
}

void displayAll(){
	pdl r;
	
	fptr = fopen("pdlRecord.txt", "r");
	if(fptr == NULL) printf("Failed to read file.");
	else{
		printf("\n=== ALL PDL RECORDS ===\n");
		while(fscanf(fptr, "%[^;];%d;%d;%[^;];%[^;];%d;%[^;];%[^;];%d;%d;%[^;];%d;%d;%[^;];%[^\n]\n",
             r.facilityCode, &r.pdl_ID, &r.noCrimes, r.pdl_name, 
             r.pdl_address.city, &r.pdl_address.zipCode, r.pdl_address.province,
             r.date_rendered.Month, &r.date_rendered.day, &r.date_rendered.year,
             r.dateOfBirth.Month, &r.dateOfBirth.day, &r.dateOfBirth.year,
             r.sex, r.status) != EOF){
                displayRecord(r);	   	
            
		 }
        
	}
	fclose(fptr);
}

void searchRecord(){
	pdl r;
    char searchfCode[15];
    int searchID, choice, searchType, found = 0;
    
    printf("Enter [1] PDL FACILITY CODE or [2] ID: ");
    while(1)
	{
		if(scanf("%d", &choice)!=1 || (choice !=1 && choice !=2))
		{
			inputError();
			continue;
		}
		clearInBuff();
		break;
	}
    
    switch(choice)
	{
        case 1: 
            printf("Enter FACILITY CODE: ");
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
    }

    fptr = fopen("pdlRecord.txt", "r");
    if(fptr == NULL){
        printf("Failed to open file!\n");
        return;
    }
    
    while(fscanf(fptr, "%[^;];%d;%d;%[^;];%[^;];%d;%[^;];%[^;];%d;%d;%[^;];%d;%d;%[^;];%[^\n]\n",
             r.facilityCode, &r.pdl_ID, &r.noCrimes, r.pdl_name, 
             r.pdl_address.city, &r.pdl_address.zipCode, r.pdl_address.province,
             r.date_rendered.Month, &r.date_rendered.day, &r.date_rendered.year,
             r.dateOfBirth.Month, &r.dateOfBirth.day, &r.dateOfBirth.year,
             r.sex, r.status) != EOF){
        
		        if(searchType == 1 && strcmp(searchfCode, r.facilityCode) == 0){
		            displayRecord(r);
		            found = 1;
		        }
		        else if(searchType == 2 && searchID == r.pdl_ID){
		            displayRecord(r);
		            found = 1;
		        }
    }
    
    if(!found)
	{
		system("cls");
        printf("RECORD NOT FOUND.\n\n");
    }
    fclose(fptr);
}

void addRecord()
{
	pdl r;
    char choice;
    
    do
	{
        r = getPdl();
        appendDocketNo(r.noCrimes, r.pdl_ID);
        fptr = fopen("pdlRecord.txt", "a");
        if(fptr == NULL){
            printf("File Failed to Open!\n");
            return;
        }
        
		fprintf(fptr, "%s;%d;%d;%s;%s;%d;%s;%s;%d;%d;%s;%d;%d;%s;%s\n", 
	        r.facilityCode, r.pdl_ID, r.noCrimes, r.pdl_name, 
	        r.pdl_address.city, r.pdl_address.zipCode, r.pdl_address.province,
	        r.date_rendered.Month, r.date_rendered.day, r.date_rendered.year,
	        r.dateOfBirth.Month, r.dateOfBirth.day, r.dateOfBirth.year,
	        r.sex, r.status);
                
            
        fclose(fptr);
        
        printf("\nAdd another record? (y/n): ");
        scanf(" %c", &choice);
        while(getchar() != '\n');
        
    }while(toupper(choice) == 'Y');
	
	system("cls");
	
}
void updateRecord()
{
	pdl r;
	
	int updateID, found = 0;
	
	printf("Enter PDL ID of ENTRY you wish to UPDATE: ");
	
	while(1)
	{
		if(scanf("%d", &updateID)!=1)
		{
			inputError();
			continue;
		}
		break;
	}
	
	fptr = fopen("pdlRecord.txt", "r");
	temp = fopen("tempRecord.txt", "w");
	
	if(fptr == NULL || temp == NULL)
	{
		printf("Error opening file.\n");
		return;
	}
	
	clearInBuff();
	
	while(fscanf(fptr, "%[^;];%d;%d;%[^;];%[^;];%d;%[^;];%[^;];%d;%d;%[^;];%d;%d;%[^;];%[^\n]\n",
				 r.facilityCode, &r.pdl_ID, &r.noCrimes, r.pdl_name, 
				 r.pdl_address.city, &r.pdl_address.zipCode, r.pdl_address.province,
				 r.date_rendered.Month, &r.date_rendered.day, &r.date_rendered.year,
				 r.dateOfBirth.Month, &r.dateOfBirth.day, &r.dateOfBirth.year,
				 r.sex, r.status) != EOF)
	{
		if(updateID==r.pdl_ID)
		{
			found = 1;
			
			printf("\n=== RECORD SELECTED ===\n");
			displayRecord(r);
			
			printf("\nENTERING NEW DATA\n\n");
			pdl newRecord = getPdl();
			
			fprintf(temp, "%s;%d;%d;%s;%s;%d;%s;%s;%d;%d;%s;%d;%d;%s;%s\n", 
					newRecord.facilityCode, newRecord.pdl_ID, newRecord.noCrimes, newRecord.pdl_name, 
					newRecord.pdl_address.city, newRecord.pdl_address.zipCode, newRecord.pdl_address.province,
					newRecord.date_rendered.Month, newRecord.date_rendered.day, newRecord.date_rendered.year,
					newRecord.dateOfBirth.Month, newRecord.dateOfBirth.day, newRecord.dateOfBirth.year,
					newRecord.sex, newRecord.status);
		}
		else
		{
			fprintf(temp, "%s;%d;%d;%s;%s;%d;%s;%s;%d;%d;%s;%d;%d;%s;%s\n", 
					r.facilityCode, r.pdl_ID, r.noCrimes, r.pdl_name, 
					r.pdl_address.city, r.pdl_address.zipCode, r.pdl_address.province,
					r.date_rendered.Month, r.date_rendered.day, r.date_rendered.year,
					r.dateOfBirth.Month, r.dateOfBirth.day, r.dateOfBirth.year,
					r.sex, r.status);
		}
	}
	fclose(fptr);
	fclose(temp);
	
	if(found)
	{
		remove("pdlRecord.txt");
		rename("tempRecord.txt", "pdlRecord.txt");
		printf("Record updated successfully!\n");
	}
	else
	{
		remove("tempRecord.txt");
		printf("Record not found!\n");
	}
}
void deleteRecord(){
	/*Creates a temp .txt file copies everything except the record that matches the deleteID and renames the temp file to the original .txt file's name*/
	pdl r;
    int deleteID = 0, recordFound = 0;

    fptr = fopen("pdlRecord.txt", "r");
    if (fptr == NULL) {
        printf("Failed to read file. No records exist yet!\n");
        return;
    }

    temp = fopen("tempRecord.txt", "w");
    if (temp == NULL) {
        printf("Failed to create temporary file!\n");
        fclose(fptr);
        return;
    }

    printf("Enter PDL ID to delete PDL record: ");
    scanf("%d", &deleteID);
    
    
    while(getchar() != '\n'); // Clear the input buffer
	deleteDocket(deleteID);
    while(fscanf(fptr, "%[^;];%d;%d;%[^;];%[^;];%d;%[^;];%[^;];%d;%d;%[^;];%d;%d;%[^;];%[^\n]\n",
             r.facilityCode, &r.pdl_ID, &r.noCrimes, r.pdl_name, 
             r.pdl_address.city, &r.pdl_address.zipCode, r.pdl_address.province,
             r.date_rendered.Month, &r.date_rendered.day, &r.date_rendered.year,
             r.dateOfBirth.Month, &r.dateOfBirth.day, &r.dateOfBirth.year,
             r.sex, r.status) != EOF) {
        
        
        if (deleteID == r.pdl_ID) {
        	// If "deleteID" matches with "r.pdl_ID" skip writing it to temp
            recordFound = 1;
            continue;
        }
        
		fprintf(temp, "%s;%d;%d;%s;%s;%d;%s;%s;%d;%d;%s;%d;%d;%s;%s\n", 
	        r.facilityCode, r.pdl_ID, r.noCrimes, r.pdl_name, 
	        r.pdl_address.city, r.pdl_address.zipCode, r.pdl_address.province,
	        r.date_rendered.Month, r.date_rendered.day, r.date_rendered.year,
	        r.dateOfBirth.Month, r.dateOfBirth.day, r.dateOfBirth.year,
	        r.sex, r.status); 
    }
	
    fclose(fptr);
    fclose(temp);

    if (recordFound != 1) {
        remove("tempRecord.txt");
        printf("Record Could not be deleted (ID not found)!\n");
    } else {
        remove("pdlRecord.txt");
        rename("tempRecord.txt", "pdlRecord.txt");
        printf("Record deleted successfully!\n");
    }
}

void inputError()
{
	printf("Input value incorrect. Please try again.\n");
	clearInBuff();
}

void clearInBuff()
{
	while(getchar()!='\n');
}
