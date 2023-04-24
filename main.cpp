#include "Classes/DynamicArray.h"
#include "Array.h"
#include "Vector.h"
#include <cstring>
#include "../cpp-cmake-demo/headers/ComplexNumber.hpp"
#include <vector>

template<typename T, size_t S = 0>
void printVector(const Vector<T>& vec) {
    for (int i = 0; i < vec.Size(); i++) 
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

struct Point {
    double x, y;
    Point(double x, double y): x(x), y(y){};
    Point(): x(0), y(0){};

};

std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << "<" << point.x << ", " << point.y << ">";
    return out;
}

int main() {
    DynamicArray arr;
    for (size_t i = 0; i < 10; i++) arr.append(i);
    std::cout << arr.size() << " " << arr.getMax() << std::endl;
    arr.append(16);
    std::cout << arr.size() << " " << arr.getMax() << std::endl;

    Array<int, 10> data;
    std::cout << data.Size() << std::endl;
    memset(data.Data(), 0, data.Size() * sizeof(int));

    Array<ComplexNumber, 5> complexArray;


    std::cout << "Vectors: \n";
    Vector<int, 10> myVec;
    std::size_t n = myVec.Capacity();
    std::cout << "n = " << n << std::endl;
    for (size_t i = 0; i < n; i++) myVec.pushBack(i);
    myVec.pushBack(31);
    std::cout << myVec << std::endl;
    myVec.pushBack(20);
    std::cout << myVec << std::endl;
    // std::cout << "Popping: " << myVec.popBack() << std::endl;
    std::cout << myVec << std::endl;

    std::cout << "Popping all: ";
    while (!myVec.isEmpty()) myVec.popBack();
    std::cout<< "after clearing" << myVec << "\n";
    myVec.assign(5, 10);
    std::cout << myVec << std::endl;
    myVec[myVec.Size() - 1] = 10;
    std::cout << "Update: " << myVec << std::endl;
    std::cout << "Clearing all:\n";
    myVec.clear();

    Vector<std::string, 5> strVec;
    strVec.pushBack("This");
    strVec.pushBack("is");
    strVec.pushBack("a");
    strVec.pushBack("string");
    strVec.pushBack("vector");
    strVec.emplace_back("emplace check");

    std::cout << "Printing Vector<std::string>: ";
    // printVector<std::string, strVec.Size()>(strVec);
    std::cout << strVec << std::endl;
    //memleak
    double* ptr = new double[10];
    ptr = nullptr;
    Vector<Point> pointVec;
    std::cout << "Point vector: " << pointVec << std::endl;
    pointVec.emplace_back(1, 2);
    pointVec.emplace_back(4, 5);
    pointVec.emplace_back(7, 1);
    std::cout << "Point Vector: " << pointVec << std::endl;

    Vector<ComplexNumber> zVec({
        ComplexNumber(1, 1),
        ComplexNumber(2, 3)
    });
    // memset((char *)0x0, 1, 100);
    zVec.emplace_back(1, 3);
    zVec.emplace_back(2.3, 4.5);
    std::cout << zVec << std::endl;

    zVec.clear();
    zVec.assign(ComplexNumber(1, 5), 5);
    std::cout << "complex assigned: " << zVec << std::endl;
    zVec[zVec.Size() - 1] = ComplexNumber(4, 9);


    // std::vector<int> std_vector({1, 2});
    // std::cout << std_vector[0] << std::endl;
    // std_vector.pop_back();
    // std_vector.pop_back();
    // std::cout << std_vector.size() << std::endl;
    // std_vector.pop_back();
    // std::cout << std_vector.size() << std::endl;
    // std_vector.emplace_back(10);
    return 0;
}