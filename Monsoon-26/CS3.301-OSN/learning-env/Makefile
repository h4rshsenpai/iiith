CC := gcc
CFLAGS := -Wall -Wextra -O2 -pthread

BIN := build/process_demo build/thread_counter build/file_copy build/udp_server build/udp_client

.PHONY: all clean run-process run-thread run-file run-scheduler run-paging run-udp-server run-udp-client

all: $(BIN)

build:
	mkdir -p build

build/process_demo: labs/processes/process_demo.c | build
	$(CC) $(CFLAGS) $< -o $@

build/thread_counter: labs/concurrency/thread_counter.c | build
	$(CC) $(CFLAGS) $< -o $@

build/file_copy: labs/filesystems/file_copy.c | build
	$(CC) $(CFLAGS) $< -o $@

build/udp_server: labs/networking/udp_server.c | build
	$(CC) $(CFLAGS) $< -o $@

build/udp_client: labs/networking/udp_client.c | build
	$(CC) $(CFLAGS) $< -o $@

run-process: build/process_demo
	./build/process_demo

run-thread: build/thread_counter
	./build/thread_counter

run-file: build/file_copy
	printf "hello from OSN\n" > build/input.txt
	./build/file_copy build/input.txt build/output.txt
	cat build/output.txt

run-scheduler:
	python3 labs/scheduling/round_robin.py

run-paging:
	python3 labs/memory/page_replacement.py

run-udp-server: build/udp_server
	./build/udp_server

run-udp-client: build/udp_client
	./build/udp_client "hello over UDP"

clean:
	rm -rf build
