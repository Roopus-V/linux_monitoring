#include<stdio.h>
#include<string.h>
#include "monitor.h"

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

