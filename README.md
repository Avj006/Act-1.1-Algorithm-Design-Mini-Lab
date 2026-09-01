# Algorithm Design Mini-Lab

This repository contains C++ implementations, pseudocode, test cases, and technical analysis for three algorithmic problems solved using distinct design paradigms: **Divide and Conquer**, **Greedy Algorithms**, and **Dynamic Programming**.

Each problem is self-contained in its own folder, with its own `main.cpp`, a dedicated `README.md` explaining the problem statement and approach, and a set of `.txt` test cases covering standard and edge-case scenarios.

---

## 📁 Repository Structure

```text
.
├── problemA_inversions/
│   ├── main.cpp            # Inversion Counter (Divide & Conquer / Merge Sort)
│   ├── MyLinkedList.h      # Custom Linked List header
│   ├── MyLinkedList.cpp    # Custom Linked List implementation
│   ├── README.md           # Problem A - documentation
│   ├── test1.txt           # Test case 1: Standard input
│   ├── test2.txt           # Test case 2: Already sorted
│   └── test3.txt           # Test case 3: Reverse sorted
├── problemB_rooms/
│   ├── main.cpp            # Minimum Meeting Rooms (Greedy / Min-Heap)
│   ├── README.md           # Problem B - documentation
│   ├── test1.txt           # Test case 1: Standard overlapping meetings
│   ├── test2.txt           # Test case 2: Back-to-back meetings
│   ├── test3.txt           # Test case 3: Fully overlapping intervals
│   └── test4.txt           # Test case 4: Nested intervals
├── problemC_knapsack/
│   ├── main.cpp            # Budgeted Study Plan (1D Dynamic Programming)
│   ├── README.md           # Problem C - documentation
│   ├── test1.txt           # Test case 1: Standard budget allocation
│   ├── test2.txt           # Test case 2: Budget too small
│   └── test3.txt           # Test case 3: Multiple module choices
├── report.txt              # Technical report (Complexity, worked examples, pseudocode, etc)
└── README.md               # Top-level repository documentation
```

---

## Problems Overview

| Problem | Paradigm | Core Technique | Time Complexity | Space Complexity |
|---|---|---|---|---|
| **A — Inversion Counter** | Divide and Conquer | Merge Sort over a created form scratch linked list, counting cross-inversions during the merge step | O(n log n) | O(log n) auxiliary (recursion stack) |
| **B — Minimum Meeting Rooms** | Greedy | Sort meetings by start time; track room availability with a min-heap of end times. Decidieng the minimum of roooms needed to host all. | O(m log m) | O(m) |
| **C — Budgeted Study Plan** | Dynamic Programming | 0/1 Knapsack solved with a 1D DP array, iterated backwards per item | O(n · T) | O(T) |

---

### Problem A — Inversion Counter (Divide & Conquer)

Counts the number of inversions in a sequence of `n` integers read directly into a custom linked list (`MyLinkedList` / `MyNoodoLL`) -> no intermediate arrays. The list is split at its middle node (fast/slow pointer technique), recursively sorted, and merged back together; every time an element from the right half is placed before a remaining element from the left half, the number of remaining left-half elements is added to a global inversion counter.

- **Input:** `n`, followed by `n` integers.
- **Output:** total number of inversions.
- **Key files:** `main.cpp`, `MyLinkedList.h`, `MyLinkedList.cpp`.

### Problem B — Minimum Meeting Rooms (Greedy)

Determines the minimum number of rooms required to host `m` meetings without overlap. Meetings are sorted by start time; a min-heap keyed on end time represents currently occupied rooms. For each meeting, if the room with the earliest end time is already free (its end time ≤ the current meeting's start time), it is reused; otherwise a new room is allocated. The final heap size is the answer.

- **Input:** `m`, followed by `m` pairs `(start, end)`.
- **Output:** minimum number of rooms needed.
- **Key file:** `main.cpp` (uses `std::priority_queue` as a min-heap).

### Problem C — Budgeted Study Plan (Dynamic Programming)

A 0/1 Knapsack variant: given `n` study modules, each with a required time and a value (learning benefit), and a maximum time budget `max_t`, finds the maximum total benefit achievable without exceeding the budget. Modules are processed one at a time (streamed, not stored), and the 1D DP array is updated **backwards** (from `max_t` down to the module's time cost) to preserve the 0/1 constraint.

- **Input:** `n`, `max_t`, followed by `n` pairs `(module_time, module_value)`.
- **Output:** maximum achievable learning benefit.
- **Key file:** `main.cpp`.

---

## Build & Run

Each problem is a standalone C++ program with no external dependencies beyond the STL. From within a problem's folder:

```bash
g++ -std=c++17 -O2 -o solution main.cpp [MyLinkedList.cpp]   # include MyLinkedList.cpp only for Problem A
./solution < test1.txt
```

Example for each problem:

```bash
# Problem A
cd problemA_inversions
g++ -std=c++17 -O2 -o solution main.cpp MyLinkedList.cpp
./solution < test1.txt
./solution < test2.txt
./solution < test3.txt

# Problem B
cd problemB_rooms
g++ -std=c++17 -O2 -o solution main.cpp
./solution < test1.txt
./solution < test2.txt
./solution < test3.txt

# Problem C
cd problemC_knapsack
g++ -std=c++17 -O2 -o solution main.cpp
./solution < test1.txt
./solution < test2.txt
./solution < test3.txt
```

---

## Additional Documentation

- Each `problemX_*/README.md` describes that problem's statement, input/output format, algorithm walkthrough, and test case explanations in detail.
- `report.txt` at the root contains the full technical analysis: complexity derivations, worked examples, and pseudocode for all three problems. As well as general logic explanation (in detail) and references used.
- This document was drafted with the assistance of Claude (Anthropic) and corrected by me.