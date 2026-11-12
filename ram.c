#include<stdio.h>
#include<string.h>
#include "monitor.h"

void mem_info(char label[], char path[]){
	char line[256];
	long total_kb = 0;
	long total_avail_kb = 0;
	double gb = 0;
	double avail_gb = 0;
	double mb = 1024.0;
	FILE *fp = fopen(path, "r");
	if(fp != NULL){
		while(fgets(line, sizeof(line), fp) != NULL){
			if(strncmp(line, "MemTotal:", 9) == 0)		    //to display total RAM size
			{
				sscanf(line, "MemTotal: %ld kB", &total_kb);
				gb = total_kb / (mb * mb );
				printf("%s: %.2lf GB", label, gb);
			}
			else if(strncmp(line, "MemAvailable:", 13) == 0){    //to display free memory available
				sscanf(line, "MemAvailable: %ld kB", &total_avail_kb);
				avail_gb = total_avail_kb / (mb * mb );
				printf("\nMemory Available: %.2lf GB", avail_gb);
			
				break;					     //to exit loop
			}
		}
									     //to display used memory in gb and %
		double used_mem = gb -avail_gb;
		double used_mem_per = (used_mem / gb) * 100;
		printf("\nMemory: %.2lf/%.2lf GB [Used: %.2lf%%] \n",used_mem, gb, used_mem_per);

		fclose(fp);
	}
}

