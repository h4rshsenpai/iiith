#!/usr/bin/env python3

from collections import deque


def round_robin(jobs, quantum):
    queue = deque({"name": name, "remaining": burst} for name, burst in jobs)
    time = 0
    timeline = []

    while queue:
        job = queue.popleft()
        ran_for = min(quantum, job["remaining"])
        start = time
        time += ran_for
        job["remaining"] -= ran_for
        timeline.append((job["name"], start, time))

        if job["remaining"] > 0:
            queue.append(job)

    return timeline


if __name__ == "__main__":
    jobs = [("A", 5), ("B", 3), ("C", 8)]
    quantum = 2

    print(f"jobs={jobs} quantum={quantum}")
    for name, start, end in round_robin(jobs, quantum):
        print(f"{start:02d}-{end:02d}: run {name}")
