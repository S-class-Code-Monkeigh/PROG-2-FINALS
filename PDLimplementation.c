#include "PDL.h"

name getName();
address getAddress();
date getDate();
pdl getPdl();

void displayRecord(pdl r);//displays singular record;
void displayAll();//displays all records
void searchRecord();//searches record based off facility code
pdl updateRecord();//returns new information for a pdl record
pdl deleteRecord();//deletes an entire record
