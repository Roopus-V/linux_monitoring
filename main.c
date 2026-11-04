#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	printf("=========================================================SYSTEM-MONITORING====================================================\n");
	printf("\n");
//os info
	char line[256];
	FILE *fp = fopen("/etc/os-release", "r");
	if(fp != NULL){
		while(fgets(line, sizeof(line), fp) != NULL){
			if(strncmp(line, "PRETTY_NAME=", 12) == 0){
				printf("%s", line);
				break;
			}
		}
		fclose(fp);
	}
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
