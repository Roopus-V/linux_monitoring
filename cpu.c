#include<stdio.h>
#include <string.h>
#include "monitor.h"

void uptime_info(char label[], char path[]){
	double uptime_seconds;
	FILE *fp = fopen(path,"r");
	if(fp != NULL){
		if(fscanf(fp, "%lf", &uptime_seconds) == 1){
			long total_seconds = uptime_seconds;	
		
			long hrs = total_seconds / 3600;      //hrs
			long minutes = (total_seconds % 3600) / 60; //minutes
			long seconds = total_seconds % 60; //seconds
		
		
			printf("%s: %02ld:%02ld:%02ld (hh:mm:ss)\n",label, hrs, minutes, seconds);
		}	
		fclose(fp);
	}
}
void cpu_info(char label[], char path[]){
	char line[256];
	FILE *fp = fopen(path, "r");
	if(fp != NULL){
		while(fgets(line, sizeof(line), fp) != NULL){
			if(strncmp(line, "model name", 10) == 0){
				printf("%s: %s", label, &line[13]);
				break;		
			}
		}
		fclose(fp);
	}
}
void cpu_time_info(char label[], char path[]){				     //to display cpu usage
	FILE *fp = fopen(path, "r");
	long user=0, nice=0, system=0, idle=0, iowait=0, irq=0, softirq=0, steal=0;
	if(fp != NULL){
		if(fscanf(fp, "cpu %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal) == 8){
			long idle_time = idle + iowait;			     //to cal total idle cpu time
			long total_time = user + nice + system + idle_time + irq + softirq + steal;// to cal total cpu usage
			long cpu_active = total_time - idle_time;	     //to cal cpu active time
			double cpu_per = ((double)cpu_active / total_time) * 100;	     //to cal cpu active time in %
			printf("%s: %.2lf%%\n",label, cpu_per);
		}
		fclose(fp);
	}	
}

