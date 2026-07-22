# Syllabus map

## Unit 1: Introduction, process and memory virtualization, networking overview

Core questions:

- Why do operating systems exist?
- What is a process?
- How does the OS switch between processes?
- What is virtual memory?
- Why do networks use layers?

Practice files:

- `labs/processes/process_demo.c`
- `labs/scheduling/round_robin.py`
- `labs/memory/page_replacement.py`

## Unit 2: Concurrency, threads, locks, data transmission, network technologies

Core questions:

- What can go wrong when two threads share data?
- What does a lock actually protect?
- What are common concurrency bugs?
- How do hosts communicate across a network?

Practice files:

- `labs/concurrency/thread_counter.c`
- `labs/networking/udp_server.c`
- `labs/networking/udp_client.c`

## Unit 3: Persistence, file systems, protection, network file systems, network security basics

Core questions:

- What does a file system abstract?
- What is the difference between file names, file descriptors, and inodes?
- How do permissions protect data?
- Why is networked storage harder than local storage?
- What are the basic goals of network security?

Practice files:

- `labs/filesystems/file_copy.c`
- Extend the UDP lab with authentication, checksums, or a simple file-transfer protocol.

## Course outcome mapping

- CO-1: Use layering notes and client/server labs to see modular design.
- CO-2: Use scheduling, locking, paging, and file labs to build OS modules.
- CO-3: Use process/thread examples to build applications on top of OS services.
- CO-4: Use `fork`, `wait`, `open`, `read`, `write`, `close`, and socket calls.
- CO-5: Use UDP/TCP socket labs and mini-projects.
