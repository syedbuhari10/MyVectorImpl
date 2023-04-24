#pragma once
#include <iostream>
#include <cassert>

class DynamicArray {
private:
    int size_;
    int max_;
    int *container_;


public:
    DynamicArray();

    ~DynamicArray();

    int size();

    int& operator[] (int i);

    void append(int data);

    int getMax();
};