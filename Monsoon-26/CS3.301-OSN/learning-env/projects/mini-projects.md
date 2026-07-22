# Mini-project ideas

## 1. Shell basics

Build a tiny shell that can:

- Read a command line.
- Run a program with `fork` and `exec`.
- Wait for foreground commands.
- Support `cd` as a built-in command.

Concepts: process API, system calls, protection boundary.

## 2. Scheduler simulator

Build a simulator for:

- FCFS.
- Round robin.
- Shortest job first.

Print average waiting time and turnaround time.

Concepts: scheduling policy, fairness, latency, throughput.

## 3. Threaded counter service

Build a server where multiple clients increment named counters.

Requirements:

- Use threads for clients.
- Protect shared counters with locks.
- Store final counter values in a file.

Concepts: threads, locks, persistence, network system calls.

## 4. File transfer over UDP

Build a client/server pair that sends a file in chunks.

Start simple:

- Send file name.
- Send numbered chunks.
- Write chunks to disk.

Then improve:

- Add checksum.
- Add acknowledgements.
- Retransmit missing chunks.

Concepts: layering, data transmission, reliability, file systems.

## Overall project: HTTP-like static file server

Build a simple server that:

- Listens on a port.
- Accepts a request for a file path.
- Checks whether the file is allowed.
- Sends file contents back to the client.
- Uses a thread per client.
- Logs requests to a file.

Concepts: system calls, protection, networking, concurrency, persistence.
