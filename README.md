# Operating Systems Practicals

**B.Sc. (Hons.) Computer Science — Semester III**

A copyable, GitHub-ready collection of the 12 practicals listed in the supplied Operating Systems practical file.

## Practical index

| No. | Practical | Main files |
|---:|---|---|
| 1 | Demonstration of OS functions using an OS simulator | `os_simulator.c` |
| 2 | Linux information, file and directory management commands | `information.sh`, `file_management.sh`, `directory_management.sh` |
| 3 | Linux process control, communication and protection | `process_control.c`, `communication.sh`, `protection.sh` |
| 4 | Parent and child processes using `fork()` / `exec()` | `same_code.c`, `different_code.c`, `wait_demo.c` |
| 5 | Linux kernel version, CPU type and CPU information | `kernel_info.c` |
| 6 | Configured, free and used memory | `memory_info.c` |
| 7 | Copy files using system calls | `copy_file.c` |
| 8 | First Come First Serve (FCFS) scheduling | `fcfs.c` |
| 9 | Shortest Job First (SJF) scheduling | `sjf.c` |
| 10 | Non-preemptive priority scheduling | `priority.c` |
| 11 | Sum of n numbers using Pthreads | `pthread_sum.c` |
| 12 | First-Fit, Best-Fit and Worst-Fit allocation | `allocation.c` |

## Requirements

- Linux (Ubuntu recommended) or WSL on Windows
- GCC compiler
- For Practical 11, POSIX threads support (`-pthread`)

Install GCC on Ubuntu:

```bash
sudo apt update
sudo apt install build-essential
```

## Compile and run C programs

Move into the required practical folder, then compile and run. Example:

```bash
cd practical-08-fcfs-scheduling
gcc fcfs.c -o fcfs
./fcfs
```

For Pthreads:

```bash
gcc pthread_sum.c -o pthread_sum -pthread
./pthread_sum
```

For shell practicals:

```bash
chmod +x information.sh
./information.sh
```

## Notes

- The practical names and order follow the supplied 28-page practical file.
- The C programs are formatted as editable source files rather than screenshots, so they can be copied directly.
- Some source-code panels in the PDF are image-only and not fully machine-readable. For those sections, the programs here are clean, runnable implementations of the exact practical stated in the file. Outputs involving dates, kernel details, memory size and process IDs will vary by system.
- Run shell commands in a test directory. Commands such as `rm`, `rmdir`, `chmod` and `chown` can change or delete files.
