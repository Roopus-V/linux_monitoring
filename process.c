#include<stdio.h>
#include<dirent.h>
#include "monitor.h"

void process_info(char label[], char path[]){
	DIR *dir = opendir(path);
	if(dir != NULL){
		struct dirent *entry;
		while((entry = readdir(dir)) != NULL){
			printf("%s :~ %s\n",label, entry->d_name);
		}
		closedir(dir);
	}
}
