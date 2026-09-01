# Problem B — Minimum Meeting Rooms (Greedy)

## Problem Statement

Given `m` meetings, each defined by a start time and an end time, determine the **minimum number of rooms** required so that no two overlapping meetings share the same room.

Two meetings overlap if their time intervals intersect; a room becomes free again the moment a meeting ends, and can immediately be reused starting at that same instant (an end time equal to the next meeting's start time does **not** count as overlap).

## Input Format

```text
m
start_1 end_1
start_2 end_2
...
start_m end_m
```

- `m`: total number of meetings.
- `m` subsequent lines, each with two integers: the start and end time of that meeting.

## Output Format

A single integer: the minimum number of rooms needed to schedule all meetings.

## Approach — Greedy with a Min-Heap

1. Read `m` and the `m` meeting intervals into a vector of pairs `(start, end)`.
2. **Sort** the meetings by start time (ascending). This lets meetings be processed in the order they begin, which is what makes the greedy strategy correct — at each step we only need to know the state of currently active rooms, never a meeting that starts later.
3. Use a **min-heap** (`priority_queue` with `greater<int>` in C++) to track the end times of meetings occupying rooms. The root of the heap is always the room that becomes free the **earliest**.
4. For each meeting, in start-time order:
   - If the heap is not empty and the room with the earliest end time (`heap.top()`) is free by the time the current meeting starts (`heap.top() <= current.start`), that room is reused: pop it from the heap.
   - Push the current meeting's end time onto the heap — this represents a room (recycled or newly allocated) now being occupied until that time.
5. After processing all meetings, the size of the heap equals the minimum number of rooms simultaneously in use, i.e., the answer.

### Why greedy works here

At any point, the number of rooms needed equals the number of meetings that are currently overlapping. By always trying to reuse the room that frees up soonest before allocating a new one, the heap size at the end of the process exactly tracks the maximum number of meetings ever active at the same time — which is the true minimum room requirement.

### Pseudocode

```text
1. Read m (number of meetings)
2. meetings = empty_list()
   For i from 1 to m:
       start, end = read_two_integers()
       meetings.append((start, end))
3. Sort meetings by start_time (ascending)
4. min_heap = empty_min_heap()   // keyed by end time
5. For current_meeting in meetings:
       If min_heap is not empty AND min_heap.top() <= current_meeting.start:
           min_heap.pop()        // reuse the earliest-freeing room
       min_heap.push(current_meeting.end)   // occupy a room
6. Return min_heap.size()        // minimum rooms needed
```

## Complexity Analysis

| Metric | Complexity | Justification |
|---|---|---|
| **Time** | `O(m log m)` | Sorting the meetings costs `O(m log m)`; each of the `m` meetings performs at most one push and one pop on a heap of size `O(m)`, each `O(log m)`. |
| **Space** | `O(m)` | The heap holds at most `m` end times, and the meetings vector stores `m` pairs. |

## Test Cases

| File | Scenario |
|---|---|
| `test1.txt` | **Standard overlapping meetings** — a general mix of overlapping and non-overlapping intervals, validating the core greedy/heap logic. |
| `test2.txt` | **Back-to-back meetings** — meetings whose end time equals the next meeting's start time; verifies that rooms are correctly reused (no false overlap) using the `<=` comparison. |
| `test3.txt` | **Fully overlapping intervals** — all meetings overlap with each other at some common point in time; the answer should equal `m` (one room per meeting). |
| `test4.txt` | **Nested intervals** — meetings fully contained within other meetings' time ranges, testing that the heap correctly tracks the earliest-ending room even when intervals are nested rather than simply sequential. |

## Build & Run

```bash
cd problemB_rooms
g++ -std=c++17 -O2 -o solution main.cpp
./solution < test1.txt
./solution < test2.txt
./solution < test3.txt
./solution < test4.txt
```

## Notes

- C++'s `std::priority_queue<int, vector<int>, greater<int>>` is used as a min-heap; the underlying push/pop/reorder operations correspond exactly to the auxiliary `Heap_Push` / `Heap_Pop` pseudocode documented at the top of `main.cpp`, included there purely for visualization of what the STL does internally.
- Sorting by start time is what allows a single linear pass with a heap to solve the problem, instead of a less efficient approach like checking every pair of meetings for overlap (`O(m²)`).