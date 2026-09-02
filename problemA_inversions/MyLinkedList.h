/*
Some code adpatation from Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia)
*/


#ifndef MYLINKEDLIST_H
#define MYLINKEDLIST_H

#include <iostream>

using namespace std;
using ll = long long;

extern ll counter_inversions; //we use extern since the porblem A has more than 1 file and we need a global accesible value for this counter

struct MyNoodoLL {
    int data; 
    MyNoodoLL* next; 

    MyNoodoLL(int data, MyNoodoLL* next) : data(data), next(next) {}
    MyNoodoLL(int data) : MyNoodoLL(data, nullptr) {}
};

class MyLinkedList {
public:
    int size;             
    MyNoodoLL* head;   
    MyNoodoLL* tail;   

    MyLinkedList();
    ~MyLinkedList();

    int length();         
    bool isEmpty() const; 

    void insertLast(int data);   
    void flush(); 

    void mergeSort();  

private:
    // Private auxiliary functions for Merge Sort
    MyNoodoLL* getMiddleNode(MyNoodoLL* head);
    MyNoodoLL* merge(MyNoodoLL* p1, MyNoodoLL* p2, MyNoodoLL*& outTail);
    MyNoodoLL* mergeSortRec(MyNoodoLL* head, MyNoodoLL*& outTail, int& outSize);
};

#endif