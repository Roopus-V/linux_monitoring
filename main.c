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
	FILE *fp = fopen(path, "r");
	if(fp != NULL){
		while(fgets(line, sizeof(line), fp) != NULL){
			if(strncmp(line, "MemTotal:", 9) == 0)
			{
				long total_kb;
				sscanf(line, "MemTotal: %ld KB", &total_kb);
				double gb = total_kb / (1024.0 * 1024.0 );
				printf("%s: %.2lf GB",label, gb);
			}
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


	printf("\n=============================================================================================================================\n");
	return 0;
}
