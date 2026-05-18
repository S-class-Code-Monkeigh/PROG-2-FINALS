#include "PDL.h"

address getAddress(){
	address a;
	printf("Enter city: ");
	fgets(a.city, sizeof(a.city), stdin);
	a.city[strcspn(a.city, "\n")] = '\0'; //removes\n (helps with formatting) by going to the index with "\n" and replacing it with \0
	do{
		printf("Enter zipcode (00000): ");
		scanf("%d", &a.zipCode);
	}while(a.zipCode > 99999 || a.zipCode < 10000);
	fflush(stdin);
	printf("Enter province: ");
	fgets(a.province, sizeof(a.province), stdin);
	a.province[strcspn(a.province, "\n")] = '\0';
	return a;

}
date getDate(){
	date d;
	printf("Enter Valid Date:\n");
	printf("Month: ");
	fgets(d.Month, sizeof(d.Month), stdin);
	d.Month[strcspn(d.Month, "\n")] = '\0';
	
	printf("Day: ");
	scanf("%d", &d.day);
	printf("Year: ");
	scanf("%d", &d.year);
	return d;
}

pdl getPdl(){
	pdl p;
	int i;
	printf("Enter Facility Code: ");
	fgets(p.facilityCode, sizeof(p.facilityCode), stdin);
	p.facilityCode[strcspn(p.facilityCode, "\n")] = '\0';
	
	printf("Enter ID number: ");
	scanf("%d", &p.pdl_ID);
	fflush(stdin);
	
	printf("Number Crimes Committed: ");
	scanf("%d", &p.noCrimes);
	fflush(stdin);
	
	printf("Enter PDL name: ");
	fgets(p.pdl_name, sizeof(p.pdl_name), stdin);
	p.pdl_name[strcspn(p.pdl_name, "\n")]='\0'; 
	
	printf("Enter Address before incarceration:\n");
	p.pdl_address = getAddress();
	
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
	p.sex[strcspn(p.sex, "\n")] ='\0';
	
	do{
		printf("Enter Marital Status: ");
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
            printf("== DOCKET NUMBERS ==\n");
            for (i = 0; i < noCrimes; i++) {
                fscanf(docketptr, "%d", &docket);
                printf("\t= Docket No. %d: %d\n", i + 1, docket);
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

    do {
    	
        printf("=== PERSON DEPRIVED OF LIBERTY RECORDS SYSTEM ===\n");
        printf("[1] - Add a Record\n");
        printf("[2] - Search/Find a Record\n");
        printf("[3] - Update/Edit a Record\n");
        printf("[4] - Delete a Record\n");
        printf("[5] - Display All Records\n");
        printf("[6] - Exit\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        fflush(stdin);
        
        system("cls");
        switch(choice) {
            case 1:
                addRecord();
                printf("Record added successfully!\n");
                break;
                
            case 2: printf("Search for a record!\n");
            	searchRecord();
                break;
                
            case 3:printf("Update a record!\n");
				updateRecord();
                break;
                
            case 4:printf("Delete a record!\n");
            	deleteRecord();
                break;
                
            case 5:printf("Dispaly all record!\n");
                displayAll(r);
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

	if(strcmp(allCap(c), "MARRIED") == 0) return 1;
	if(strcmp(allCap(c), "SINGLE") == 0) return 1;
	if(strcmp(allCap(c), "DIVORCED")== 0) return 1;
	if(strcmp(allCap(c), "SEPERATED")== 0) return 1;
	if(strcmp(allCap(c), "WIDOWED")== 0) return 1;
	
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
    docketNoDisplay(r.pdl_ID);
    printf("\n");
}

void displayAll(){
	pdl r;
	
	fptr = fopen("pdlRecord.txt", "r");
	if(fptr == NULL) printf("Failed to read file.");
	else{
		printf("\n=== ALL PDL RECORD ===\n");
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
	
}
void updateRecord()
{
	pdl r;
	
	int updateID, found = 0;
	
	printf("Enter PDL ID of ENTRY you wish to UPDATE:\n> ");
	
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
			
			printf("\n=== CURRENT RECORD ===\n");
			displayRecord(r);
			
			printf("\n=== ENTER NEW DATA ===\n");
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
	pdl r;
    int deleteID = 0, recordFound = 0;

    // Open original for reading, temp for writing
    fptr = fopen("pdlRecord.txt", "r");
    if (fptr == NULL) {
        printf("Failed to read file. No records exist yet.\n");
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

