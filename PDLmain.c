#include "PDLimplementation.c"

int main(){
	pdl p;
	do{
		printf("Please enter, Married, Single, Divorced, Seperated, Widowed: ");
		scanf("%s", p.status);
	}while(isStatusValid(p.status) == 0);
	
}
