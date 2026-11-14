#ifndef MONITOR_H
#define MONITOR_H

	void os_info(char label[], char path[]);
	void proc_info(char label[], char path[]);
	void uptime_info(char label[], char path[]);
	void cpu_info(char label[], char path[]);
	void mem_info(char label[], char path[]);
	void cpu_time_info(char label[], char path[]);
	void disk_info(char label[], char path[]);
	void process_info(char label[], char path[]);
	int is_pid(const char *str);		//related ti process_info (process.c)
#endif
