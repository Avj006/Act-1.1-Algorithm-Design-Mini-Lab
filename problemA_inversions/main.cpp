/*
Some code adpatation from Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia)
*/

#include <iostream>
#include "MyLinkedList.h"

using namespace std;
using ll = long long;

/* 
Pseudocode
4. Initialize global counter (for inversions)
counter_inversions = 0
*/
long long counter_inversions = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /* 
    Pseudocode
    1. Receive number n, which represents the total amount of elements.
    */
    int n;
    if (!(cin >> n)) return 0;
    
    MyLinkedList lista;

    /* 
    Pseudocode
    2. Receive the n numbers separated by spaces + validate that it matches n.
    3. Linked List (while reading: no intermediate arrays) 
    */
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        lista.insertLast(val); // Pseudocode 3: Call insertLast(input) for each element read
    }

    // Sort the list and count inversions
    lista.mergeSort();

    /* 
    Pseudocode
    8. Return counter
    */
    // TODO: Print counter_inversions
    // cout << counter_inversions << "\n";

    return 0;
}
