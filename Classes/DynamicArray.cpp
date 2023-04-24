#include "DynamicArray.h"

DynamicArray::DynamicArray() 
:   size_(0),
    max_(5),
    container_(new int[5])
    {}

DynamicArray::~DynamicArray() {
    delete[] this->container_;
}

int DynamicArray::size() { return size_; }

int DynamicArray::getMax() { return max_; }

int& DynamicArray::operator[] (int i) {
    assert(i < size_);
    return container_[i];
}

void DynamicArray::append(int data) {
    if (size_ + 1 > max_) {
        max_ *= 2;
        int *tmp = new int[max_];
        for (size_t i = 0; i < size_; i++) 
            tmp[i] = container_[i];
        tmp[size_] = data;
        delete[] container_;
        container_ = tmp;
        size_++;
    }
    else container_[size_++] = data;
}
