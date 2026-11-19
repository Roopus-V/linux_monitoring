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
int is_vmrss(const char *str){
        char line[256];
        snprintf(line, sizeof(line), "/proc/%s/status", str);
        FILE *fp = fopen(line, "r");
        if(fp == NULL){
                return 0;
        }
                char status[256];
                while(fgets(status, sizeof(status), fp) != NULL){
                        if(strncmp(status, "VmRSS:", 6) == 0){
                                fclose(fp);
                                return 1;
                        }
                }
                fclose(fp);
                return 0;
}

void name(const char *pid){
	char comm[256];
	snprintf(comm, sizeof(comm), "/proc/%s/comm", pid);
	FILE *fp = fopen(comm, "r");
	if(fp != NULL){
		char line[256];
		if(fgets(line, sizeof(line), fp) != NULL){
			line[strcspn(line, "\n")] = '\0';
			printf(" Name: %-27s",line);
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
				line[strcspn(line, "\n")] = '\0';
				printf(" %-21s",line);
				break;
			}
		}
		fclose(fp);
	}
}
void memory(const char *pid){
	char status[256];
	char vm_rss[256] = "VmRss:\t   N/A";
	snprintf(status, sizeof(status), "/proc/%s/status", pid);
	FILE *fp = fopen(status, "r");
	if(fp != NULL){
		char line[256];
		while(fgets(line, sizeof(line), fp) != NULL){
			if(strncmp(line, "VmRSS:", 6) == 0){
				line[strcspn(line, "\n")] = '\0';
				snprintf(vm_rss, sizeof(vm_rss),"%s",line);
				break;
			}
		}
		fclose(fp);
	}
	printf(" %s",vm_rss);
}

void process_info(char label[], char path[]){
	DIR *dir = opendir(path);
	if(dir != NULL){
		struct dirent *entry;
		int count = 0;
		while((entry = readdir(dir)) != NULL){
	                int func1 = is_pid(entry->d_name);
                        int func2 = is_vmrss(entry->d_name);
			if(count == 10) break;
			if(func1 && func2){			//to print only processes with pid
				count++;
				printf("%-6d %s : %-6s",count, label, entry->d_name);
				name(entry->d_name); 			//calling function to get name of the pid
				status(entry->d_name);  		//calling function to get status of the pid
				memory(entry->d_name);  		//calling function to get ram usage of the pid
				printf("\n");
			}
		}
		closedir(dir);
	}
}

