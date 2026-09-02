# Problem C — Budgeted Study Plan (Dynamic Programming)

## Problem Statement

A student has a limited amount of study time (`max_t`) and a list of `n` candidate study modules. Each module `i` requires a certain amount of time (`time_i`) to complete and yields a certain learning benefit/value (`value_i`) if completed. Each module can be taken **at most once** (0/1 choice — take it fully or skip it, no partial credit).

The goal is to choose a subset of modules whose total required time does not exceed `max_t`, while **maximizing the total learning benefit**.

This is a direct instance of the classic **0/1 Knapsack Problem**:
- Knapsack capacity → `max_t`
- Item weight → `module_time`
- Item value → `module_value`

## Input Format

```text
n
max_t
module_time_1 module_value_1
module_time_2 module_value_2
...
module_time_n module_value_n
```

- `n`: total number of study modules.
- `max_t`: maximum available study time (the budget).
- `n` subsequent lines, each with two integers: the time cost and the value/benefit of that module.

## 📤 Output Format

A single integer: the maximum total learning benefit achievable without exceeding `max_t`.

## Approach — 1D Dynamic Programming (Space-Optimized 0/1 Knapsack)

1. Read `n` and `max_t`.
2. Initialize a 1D DP array `dp` of size `max_t + 1`, all entries set to `0`. `dp[w]` represents the best achievable benefit using **exactly up to `w`** units of time.
3. Read modules **one at a time** (not stored in an auxiliary array/list) — as soon as a module's `time` and `value` are read, the DP array is updated immediately using it.
4. For each module, iterate `w` from `max_t` down to `module_time` (**backwards**):
   - `dp[w] = max(dp[w], dp[w - module_time] + module_value)`
   - This chooses the better of: *skip the module* (`dp[w]` stays the same) or *take the module* (`dp[w - module_time] + module_value`).
5. Iterating backwards is essential: it guarantees each module is considered **at most once** per capacity value, preserving the 0/1 constraint (a forward iteration would allow reusing the same module multiple times, turning this into an unbounded knapsack).
6. After processing all `n` modules, `dp[max_t]` holds the maximum achievable benefit within the full time budget. Print it.

### Pseudocode

```text
1. Read n (number of modules)
2. Read max_t (time budget)
3. dp = array of size (max_t + 1), all initialized to 0
4. For i from 0 to n - 1:
       current_time, current_value = read_two_integers()
       For w from max_t down to current_time:
           skip_module = dp[w]
           take_module = dp[w - current_time] + current_value
           dp[w] = max(skip_module, take_module)
5. Return dp[max_t]
```

## ⏱️ Complexity Analysis

| Metric | Complexity | Justification |
|---|---|---|
| **Time** | `O(n · T)` | Outer loop runs `n` times (one per module); inner loop runs up to `max_t` or `T` times. |
| **Space** | `O(T)` | Only a single 1D array of size `max_t + 1` or `T + 1` is kept; modules are streamed in without extra storage, so no `O(n)` item array is needed. |

This is an improvement over the naive 2D DP formulation (`O(n · T)` time but `O(n · T)` space), since only the previous "row" of the DP table is ever needed — achieved here by updating the array in place, backwards.

## 🧪 Test Cases

| File | Scenario |
|---|---|
| `test1.txt` | **Standard budget allocation** — a typical mix of modules where some combination of them fits within the budget; validates the general DP recurrence. |
| `test2.txt` | **Budget too small** — `max_t` is smaller than the cheapest module's time cost, so no module can be selected; expected output is `0`. |
| `test3.txt` | **Multiple module choices** — several modules compete for the same budget, testing that the algorithm correctly picks the combination maximizing total value rather than a greedy-by-value or greedy-by-time choice. |

## ⚙️ Build & Run

```bash
cd problemC_knapsack
g++ -std=c++17 -O2 -o solution main.cpp
./solution < test1.txt
./solution < test2.txt
./solution < test3.txt
```

## Notes

- The solution deliberately avoids the greedy strategy (e.g., picking modules by best value/time ratio) because that does **not** guarantee optimality for 0/1 Knapsack — DP is required to consider all valid subsets implicitly.
- Values are read directly inside the outer loop without being stored in an intermediate vector, keeping memory usage minimal and proportional only to `max_t`.
- This document was drafted with the assistance of Claude (Anthropic) and corrected by me.