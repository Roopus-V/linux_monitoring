#include<stdio.h>
#include<stdlib.h>
int main(){
	printf("=========================================================SYSTEM-MONITORING====================================================\n");
	printf("\n");
//os info
	char line[256];
	FILE *fp = fopen("/etc/os-release", "r");
	if(fgets(line, sizeof(line), fp) != NULL){
		printf("%s", line);
	}
	fclose(fp);
//
	printf("Kernel: ");
	fflush(stdout);
	system("uname -s");
	printf("Architecture: ");
	fflush(stdout);
	system("uname -m");

	printf("\n=============================================================================================================================\n");
	return 0;
}
