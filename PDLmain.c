#include "PDLimplementation.c"

int main(){
	date d;
	do{
		d = getDate();
	}while(isdateValid(d) == 0);
	
}
