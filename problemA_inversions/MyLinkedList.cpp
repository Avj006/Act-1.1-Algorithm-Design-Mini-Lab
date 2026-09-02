/*
Some code adpatation from Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia)
*/

#include "MyLinkedList.h"

// Time Complexity: O(1) - Only three variables are initialized.
// Space Complexity: O(1) - No extra dynamic memory is allocated.
MyLinkedList::MyLinkedList() {  
    this->size = 0;
    this->head = this->tail = nullptr;
}

// Time Complexity: O(n) - Calls flush(), which traverses all n nodes to delete them.
// Space Complexity: O(1) - Only temporary pointers are used.
MyLinkedList::~MyLinkedList() { 
    flush();
}

// Time Complexity: O(1) - Directly returns the instance variable.
// Space Complexity: O(1) - No extra memory required.
int MyLinkedList::length() {
    return this->size;
}

// Time Complexity: O(1) - Simple mathematical comparison.
// Space Complexity: O(1) - No extra memory required.
bool MyLinkedList::isEmpty() const {
    return this->size == 0;
}

/* 
Time Complexity: O(1) - Directly inserts using the 'tail' pointer without traversing the list.
Space Complexity: O(1) auxiliary (only one new node is created).

Pseudocode
A. Function insertLast(data):
    Create a new node 'newNode' with 'data'
    If the list isEmpty:
        head = newNode
        tail = newNode
    Else:
        tail.next = newNode
        tail = newNode
    Increase list size
*/
void MyLinkedList::insertLast(int data) {
    if (isEmpty()) {
        MyNoodoLL* nuevo = new MyNoodoLL(data, this->head);
        this->head = nuevo;
        this->tail = nuevo;
        this->size++;
        return;
    }
    MyNoodoLL* nuevo = new MyNoodoLL(data);
    this->tail->next = nuevo;
    this->tail = nuevo;
    this->size++;
}

// Time Complexity: O(n) - Traverses all nodes in the list to free their memory.
// Space Complexity: O(1) - Only uses auxiliary variables to avoid losing the link.
void MyLinkedList::flush() { 
    MyNoodoLL* current = this->head;
    while (current != nullptr) {
        MyNoodoLL* next = current->next;
        delete current;
        current = next;
    }
    this->head = this->tail = nullptr;
    this->size = 0;
}

/* 
Time Complexity: O(n) - The fast/slow pointers iteratively traverse half the list.
Space Complexity: O(1) - Only local pointers are used.

Pseudocode
B. Function getMiddleNode(head):
    If list has 0 or 1 element, return head
    slow = head
    fast = head.next
    While fast != null and fast.next != null:
        slow = slow.next
        fast = fast.next.next
    midNext = slow.next
    slow.next = null // Disconnection of pointers: two independent halves
    return midNext
*/
MyNoodoLL* MyLinkedList::getMiddleNode(MyNoodoLL* h) { 
    if (h == nullptr || h->next == nullptr) return h; 

    MyNoodoLL* slow = h;
    MyNoodoLL* fast = h->next; 

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    MyNoodoLL* head2 = slow->next; 
    slow->next = nullptr; 
    return head2;
}

/* 
Time Complexity: O(n) - Where n is the combined number of elements in p1 and p2; traverses both sublists completely once.
Space Complexity: O(1) auxiliary - Existing nodes are reconnected (in-place) using a local dummy node.

Pseudocode
6. If left element > right element -> increase counter (+1): (+ length(left))
merge(left, right):
*/
MyNoodoLL* MyLinkedList::merge(MyNoodoLL* left, MyNoodoLL* right, MyNoodoLL*& outTail) { 
    /* 
    Pseudocode
    6.1 Create a dummyNode to build the new merged list, and set current = dummyNode.
    */
    MyNoodoLL dummy(0, nullptr); 
    MyNoodoLL* current = &dummy;

    /* 
    Pseudocode
    while (left != null and right != null):
    */
   int inversions = 0;
   MyNoodoLL* temp = left;
   while (temp != nullptr) {
    inversions++;
    temp = temp->next;
    }

    while (left != nullptr && right != nullptr) {
        if (left->data <= right->data) {
            current->next = left;
            left = left->next;
            inversions--;
        } else {
            current->next = right;
            right = right->next;
            
            /*
            Pseudocode (Checks inversion):
            //Update counter:
            counter_inversions = counter_inversions + length(left)
            */
            // TODO: Add the number of remaining nodes in 'left' to the global counter
            counter_inversions += inversions;
        }
        current = current->next;
    }

    /* 
    Pseudocode
    7. Reorder (reintegration of list) -> end of merge & counter ready
    //Link the remaining nodes from whichever list is not empty.
    */
    current->next = (left != nullptr ? left : right); 

    // Calculate tail by iterating over the remainders (Takes at most O(n))
    MyNoodoLL* t = current;
    while (t->next != nullptr) {
        t = t->next;
    }
    outTail = t;

    return dummy.next; 
}

/* 
Time Complexity: O(n log n) - Recursively divides the list (log n depth) and joins the subproblems using merge in O(n) time per level.
Space Complexity: O(log n) - Related to the call stack size due to recursion. No additional node memory is allocated.

Pseudocode
5. If list >1 element: divide in half (recursive)
*/
MyNoodoLL* MyLinkedList::mergeSortRec(MyNoodoLL* h, MyNoodoLL*& outTail, int& outSize){ 
    if (h == nullptr || h->next == nullptr) {
        outTail = h;
        outSize = (h != nullptr ? 1 : 0);
        return h;
    }

    MyNoodoLL* head2 = getMiddleNode(h); 

    int size1, size2;
    MyNoodoLL* tail1;
    MyNoodoLL* tail2;

    MyNoodoLL* part1 = mergeSortRec(h, tail1, size1); 
    MyNoodoLL* part2 = mergeSortRec(head2, tail2, size2);

    MyNoodoLL* newTail;
    MyNoodoLL* newHead = merge(part1, part2, newTail);

    outTail = newTail;
    outSize = size1 + size2;
    return newHead; 
}

// Time Complexity: O(n log n) - Delegates all the work to mergeSortRec.
// Space Complexity: O(log n) - Due to the internal recursion call stack.
void MyLinkedList::mergeSort() { 
    if (!head || !head->next) {
        return;
    }
    int nuevoSize = 0;
    MyNoodoLL* nuevoTail = nullptr;
    
    head = mergeSortRec(head, nuevoTail, nuevoSize); 
    
    tail = nuevoTail;
    size = nuevoSize;
}