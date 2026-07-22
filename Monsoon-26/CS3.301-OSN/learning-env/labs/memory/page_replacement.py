#!/usr/bin/env python3


def fifo_page_replacement(references, frame_count):
    frames = []
    faults = 0

    for page in references:
        hit = page in frames
        if not hit:
            faults += 1
            if len(frames) == frame_count:
                frames.pop(0)
            frames.append(page)

        state = "hit " if hit else "fault"
        print(f"page={page} {state} frames={frames}")

    print(f"page faults={faults}")


if __name__ == "__main__":
    refs = [1, 2, 3, 2, 4, 1, 5, 2, 1, 2, 3, 4]
    fifo_page_replacement(refs, frame_count=3)
