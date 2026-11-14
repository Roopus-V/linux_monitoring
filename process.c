#include<stdio.h>
#include<dirent.h>
#include<ctype.h>
#include<string.h>
#include "monitor.h"
int is_pid(const char *str){//const so no changes can made in the str	//passing *memory address where the string starts(lives)
	int len = strlen(str);
	if(str == NULL || *str == '\0') return 0;
		
	for(int i=0; i<len; i++){
		if(!isdigit(str[i])){
			return 0;				//found a letter(non-digit)
		}
	}
	return 1;						//found a digit
}

void combine(const char *pid){
	char comm[256];
	snprintf(comm, sizeof(comm), "/proc/%s/comm", pid);
	FILE *fp = fopen(comm, "r");
	if(fp != NULL){
		char line[256];
		if(fgets(line, sizeof(line), fp) != NULL){
			line[strcspn(line, "\n")] = '\0';
			printf(" Name: %-25s",line);
		}
		fclose(fp);
	}
}
void status(const char *pid){
	char status[256];
	snprintf(status, sizeof(status), "/proc/%s/status", pid);
	FILE *fp = fopen(status, "r");
	if(fp != NULL){
		char line[256];
		while(fgets(line, sizeof(line), fp) != NULL){
			if(strncmp(line, "State:", 6) == 0){
				printf(" %s",line);
				break;
			}
		}
		fclose(fp);
	}
}

void process_info(char label[], char path[]){
	DIR *dir = opendir(path);
	if(dir != NULL){
		struct dirent *entry;
		int count = 0;
		while((entry = readdir(dir)) != NULL){
			if(count == 10) break;
			if(is_pid(entry->d_name)){			
				count++;
				printf("%-6d %s : %-6s",count, label, entry->d_name);
				combine(entry->d_name); 
				status(entry->d_name); 
			}
		}
		closedir(dir);
	}
}

