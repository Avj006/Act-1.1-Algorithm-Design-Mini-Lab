# Problem A — Inversion Counter (Divide & Conquer)

## Problem Statement

Given a sequence of `n` integers, count the total number of **inversions** in it. An inversion is a pair of indices `(i, j)` such that `i < j` but the element at position `i` is greater than the element at position `j` (i.e., the pair is "out of order" relative to ascending sort).

The sequence must be read directly into a **custom singly linked list** (`MyLinkedList` / `MyNoodoLL`) as the numbers are provided — no intermediate arrays are used to store the input.

## Input Format

```text
n
val_1 val_2 val_3 ... val_n
```

- `n`: total number of elements.
- A single line (or stream) with `n` integers separated by spaces, inserted one by one into the linked list via `insertLast`.

## Output Format

A single integer: the total number of inversions found in the sequence.

## Approach — Modified Merge Sort on a Linked List

Counting inversions naively requires comparing every pair of elements (`O(n²)`). Instead, this solution counts inversions **as a side effect of merge sort**, bringing the cost down to `O(n log n)`.

1. Read `n` values and insert them into `MyLinkedList` in input order via `insertLast` (`O(1)` per insertion thanks to the `tail` pointer).
2. Recursively split the list in half using the **fast/slow pointer technique** (`getMiddleNode`): the slow pointer advances one node at a time, the fast pointer two, so when the fast pointer reaches the end, the slow pointer sits at the middle. The list is then physically disconnected into two independent sublists.
3. Recursively sort each half (`mergeSortRec`) until sublists of size 0 or 1 are reached (already sorted, zero inversions).
4. **Merge** the two sorted halves back together (`merge`), and this is where inversions are counted:
   - Walk both sublists with two pointers, `left` and `right`.
   - If `left->data <= right->data`, take the node from `left` — no inversion, since it's already in the correct relative order.
   - If `left->data > right->data`, take the node from `right` instead. This means **every remaining node in `left`** (the current node and all nodes after it) forms an inversion with this `right` node, since they are all greater than it but were positioned earlier in the original sequence. Add the count of remaining `left` nodes to the global `counter_inversions`.
5. Once merging completes at the top level (after all recursive levels), `counter_inversions` holds the total number of inversions in the original sequence.

### Pseudocode

```text
1. Receive n (total number of elements)
2. Receive n numbers, inserting each directly into a linked list (insertLast)
3. counter_inversions = 0  (global)

Function getMiddleNode(head):
    slow = head, fast = head.next
    While fast != null and fast.next != null:
        slow = slow.next
        fast = fast.next.next
    midNext = slow.next
    slow.next = null
    return midNext

Function merge(left, right):
    dummy = new empty node, current = dummy
    remaining_left = length(left)
    While left != null and right != null:
        If left.data <= right.data:
            current.next = left; left = left.next
            remaining_left = remaining_left - 1
        Else:
            current.next = right; right = right.next
            counter_inversions += remaining_left
        current = current.next
    current.next = (left != null) ? left : right
    return dummy.next

Function mergeSortRec(head):
    If head == null or head.next == null: return head
    mid = getMiddleNode(head)
    left = mergeSortRec(head)
    right = mergeSortRec(mid)
    return merge(left, right)

4. mergeSort() // sorts the list and populates counter_inversions as a side effect
5. Return counter_inversions
```

## Complexity Analysis

| Metric | Complexity | Justification |
|---|---|---|
| **Time** | `O(n log n)` | Merge sort recursion depth is `log n`; each level performs `O(n)` total work across `getMiddleNode` and `merge`. |
| **Space** | `O(log n)` auxiliary | No extra node/array storage is allocated — nodes are relinked in place. The only overhead is the recursive call stack, proportional to the recursion depth. |

This is a significant improvement over the brute-force `O(n²)` pairwise comparison approach.

## Test Cases

| File | Scenario |
|---|---|
| `test1.txt` | **Standard input** — a general unordered sequence, validating the overall inversion count against a typical case. |
| `test2.txt` | **Already sorted** — a fully ascending sequence; expected output is `0` inversions. |
| `test3.txt` | **Reverse sorted** — a fully descending sequence; this is the worst case, producing the maximum possible number of inversions, `n(n-1)/2`. |

## Build & Run

```bash
cd problemA_inversions
g++ -std=c++17 -O2 -o solution main.cpp MyLinkedList.cpp
./solution < test1.txt
./solution < test2.txt
./solution < test3.txt
```

## Notes

- `counter_inversions` is declared as a global `long long` (`extern` in `MyLinkedList.h`) so it can be shared and updated across `main.cpp` and `MyLinkedList.cpp`, and to avoid overflow on large inputs where the inversion count can grow up to `O(n²)`.
- The linked list is intentionally used (instead of a `vector`) to reuse and extend the custom data structure built in a prior activity ("Act 2.3 — Actividad Integral estructura de datos lineales"), and to demonstrate merge sort's natural fit for linked structures — no random access is needed, unlike array-based merge sort variants.
- This document was drafted with the assistance of Claude (Anthropic) and corrected by me.
