#include<stdio.h>
#include<stdlib.h>
int main(){
	char s[]= "Ubuntu";
	printf("=========================================================SYSTEM-MONITORING====================================================\n");
	printf("\n");
	printf("Operating System: %s \n",s);
	
	system("cat /etc/os-release | head -n 1");
	printf("Kernel: ");
	fflush(stdout);
	system("uname -s");
	printf("Architecture: ");
	fflush(stdout);
	system("uname -m");

	printf("\n=============================================================================================================================\n");
	return 0;
}
