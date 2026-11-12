#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/statvfs.h>
#include "monitor.h"

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
	cpu_time_info("CPU Usage", "/proc/stat");
	disk_info("Disk info","/");

	printf("\n=============================================================================================================================\n");
	return 0;
}
