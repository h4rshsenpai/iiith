# Study plan

## Week 1: OS basics and processes

- Read: OSTEP chapters on introduction, processes, and process API.
- Watch: NPTEL operating systems lectures on OS overview and processes.
- Run: `make run-process`.
- Modify: print process IDs before and after `fork`.

## Week 2: Scheduling

- Read: OSTEP chapters on scheduling.
- Run: `make run-scheduler`.
- Modify: change the time quantum and compare completion times.

## Week 3: Memory virtualization

- Read: OSTEP chapters on address spaces, paging, and virtual memory.
- Run: `make run-paging`.
- Modify: replace FIFO with LRU.

## Week 4: Threads and locks

- Read: OSTEP chapters on threads, locks, and condition variables.
- Run: `make run-thread`.
- Modify: remove the lock, rerun many times, and observe the race.

## Week 5: File systems and protection

- Read: OSTEP chapters on file systems and persistence.
- Run: `make run-file`.
- Modify: print how many bytes each `read` call returns.

## Week 6: Networking fundamentals

- Read: Tanenbaum chapters on network models, physical/data link basics, IP, and transport.
- Watch: NPTEL computer networks lectures on layering, IP, UDP, and TCP.
- Run: UDP server and client.
- Modify: send structured messages like `name:message`.

## Week 7: Integration project

Build a small networked application that uses processes, threads, files, and sockets.

Good choices:

- Concurrent chat server.
- File transfer tool.
- HTTP-like static file server.
- Remote command runner with strict command allowlist.
