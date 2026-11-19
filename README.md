# Linux System Monitor (C)

A command-line Linux system monitoring utility written in C as a personal learning project, built incrementally using a phased approach.

## Current Status

Work in progress. Completed so far:

- **System & OS Information (`os.c`):** Reads distribution details from `/etc/os-release` and kernel metadata (`hostname`, `ostype`, `osrelease`) from `/proc/sys/kernel/`
- **CPU & Uptime (`cpu.c`):** Displays system uptime from `/proc/uptime`, CPU model name from `/proc/cpuinfo`, and active CPU usage percentage from `/proc/stat`
- **Memory (`ram.c`):** Parses `/proc/meminfo` (`MemTotal` and `MemAvailable`) to show total, available, and used memory in GB along with usage percentage.
- **Disk Storage (`disk.c`):** Uses `statvfs()` on `/` to display total, used, and available storage in GB.
- **Process Listing (`process.c`):** Scans `/proc` for numeric PIDs, reads process names (`/proc/<pid>/comm`) and states (`/proc/<pid>/status`), filters processes that report `VmRSS`, and prints aligned output for up to 10 matching processes.

## Planned Phases

- Deeper resource monitoring (disk/network and extended metrics)
- Interactive CLI capabilities

## Building and Running

Requires `gcc` on a Linux system:

```bash
gcc -Wall -Wextra main.c os.c cpu.c ram.c disk.c process.c -o monitor
./monitor
