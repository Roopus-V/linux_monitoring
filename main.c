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
void cpu_time_info(char label[], char path[]){				     //to display cpu usage
	char line[256];
	FILE *fp = fopen(path, "r");
		long user=0, nice=0, system=0, idle=0, iowait=0, irq=0, softirq=0, steal=0;
	if(fp != NULL){
		if(fscanf(fp, "cpu %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal) == 8){
			long idle_time = idle + iowait;			     //to cal total idle cpu time
			long total_time = user + nice + system + idle_time + irq + softirq + steal;// to cal total cpu usage
			long cpu_active = total_time - idle_time;	     //to cal cpu active time
			double cpu_per = ((double)cpu_active / total_time) * 100;	     //to cal cpu active time in %
			printf("CPU Usage: %.2lf", cpu_per);
		}
		fclose(fp);
	}	
}

int main(){
	printf("=========================================================SYSTEM-MONITORING====================================================\n");
	printf("\n");

	os_info("PRETTY NAME", "/etc/os-release");		//calling function to display pretty name
	proc_info("HOSTNAME", "/proc/sys/kernel/hostname");	//calling function to display info from proc
	proc_info("OS TYPE", "/proc/sys/kernel/ostype");
	proc_info("OS RELEASE", "/proc/sys/kernel/osrelease");
	uptime_info("Raw Uptime", "/proc/uptime"); 		//calling function to display system uptime
	cpu_info("Model name", "/proc/cpuinfo");		//calling function to display system cpuinfo
	mem_info("Total Memory", "/proc/meminfo");		//calling function to display system
	cpu_time_info("CPU Time", "/proc/stat");

	printf("\n=============================================================================================================================\n");
	return 0;
}
