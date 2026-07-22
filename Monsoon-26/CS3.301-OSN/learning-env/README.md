# Operating Systems and Networks learning environment

This directory is a simple workspace for learning the course concepts by reading short notes and running small programs.

## Layout

- `notes/` contains concept maps, study order, and source recommendations.
- `labs/` contains tiny runnable examples for each unit.
- `projects/` contains mini-project ideas aligned with the course outcomes.

## Quick start

From this directory:

```sh
make
make run-process
make run-thread
make run-file
make run-scheduler
make run-paging
make run-udp-server
```

In another terminal, while the UDP server is running:

```sh
make run-udp-client
```

To remove compiled files:

```sh
make clean
```

## Recommended learning loop

1. Read the matching file in `notes/`.
2. Run the smallest lab for that topic.
3. Modify one variable or line of code.
4. Explain the behavior in your own words in `notes/my-notes.md`.
5. Build one mini-project from `projects/mini-projects.md`.

Prioritize understanding over memorizing APIs. For this course, the key habit is to connect high-level OS/network ideas to concrete system calls and program behavior.
