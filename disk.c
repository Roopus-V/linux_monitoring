#include<stdio.h>
#include "monitor.h"
#include<sys/statvfs.h>
void disk_info(char label[], char path[]){				     //to display storage (hard disk) info
	struct statvfs disk;
	if(statvfs(path, &disk) ==0){
		double gb = 1024.0 * 1024.0 * 1024.0;			     //Bytes=> kB => GB
		double total_gb = (double)(disk.f_blocks * disk.f_frsize) / gb;//Total storage in GB
		double avail_gb = (double)(disk.f_bavail * disk.f_frsize) / gb;
		printf("%s: [Total Size: %.2lfGB, Used: %.2lfGB, Available storage: %.2lfGB]\n",label, total_gb,(total_gb-avail_gb), avail_gb);
	}
}

