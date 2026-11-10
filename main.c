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
				int len = strlen(line);
				line[len - 2] = '\0';
				printf("Distro: %s\n", &line[13]);
				break;
			}
		}
		fclose(fp);
	}


	//proc info
	fp = fopen("/proc/sys/kernel/hostname", "r");
	if(fgets(line, sizeof(line), fp) != NULL){
			//	int len = strlen(line);
			//	line[len - 2] = '\0';
				printf("Hostname: %s\n",line);
			//	printf("Distro: %s\n", &line[13]);
			//	break;
			
		fclose(fp);
	}
	



	printf("\n=============================================================================================================================\n");
	return 0;
}
