#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void proc_info(char label[], char path[]){
	char line[256];
	FILE *fp = fopen(path, "r");
	if(fp != NULL){
		if(fgets(line, sizeof(line), fp) != NULL){
					printf("%s: %s",label, line);
		}
		fclose(fp);
	}
}
void os_info(char label[], char path[]){
	char line[256];
	FILE *fp = fopen(path, "r");
	if(fp != NULL){
		while(fgets(line, sizeof(line), fp) != NULL){
			if(strncmp(line, "PRETTY_NAME=", 12) == 0){
				int len = strlen(line);
				line[len - 2] = '\0';
				printf("%s: %s\n",label, &line[13]);
				break;
			}
		}
		fclose(fp);
	}
}

int main(){
	printf("=========================================================SYSTEM-MONITORING====================================================\n");
	printf("\n");

	os_info("PRETTY NAME","/etc/os-release");
	proc_info("HOSTNAME","/proc/sys/kernel/hostname");
	proc_info("OS TYPE","/proc/sys/kernel/ostype");
	proc_info("OS RELEASE","/proc/sys/kernel/osrelease");

	printf("\n=============================================================================================================================\n");
	return 0;
}
