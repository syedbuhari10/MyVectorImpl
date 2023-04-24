#include <iostream>
#include <cassert>

template <typename T, size_t S = 0>
class Vector {
private:
    size_t m_size = 0;
    size_t m_capacity = 0;

    void reallocate(size_t newCapacity) {
        T* temp = new T[newCapacity];

        if (newCapacity < m_size)
            m_size = newCapacity;

        //copy old contents to new
        for (int i = 0; i < m_size; i++)
            temp[i] = std::move(m_Data[i]);

        //delete old data
        delete[] m_Data;
        m_Data = temp;
        m_capacity = newCapacity;
    }

public:
    T* m_Data = nullptr;

    Vector() {
        reallocate(S);
    }

    // Vector(size_t newCapacity) {
    //     reallocate(newCapacity);
    // }

    Vector(size_t newCapacity);

    template <class ...Args>
    Vector(Args&& ...args) {
        std::size_t n = sizeof...(Args);
        if (n > 1) reallocate(n);
        else reallocate(S);
        // std::cout << "S= " << S << std::endl;
        (pushBack(args), ...);
        // ((std::cout << "test" << args << " "), ...);

    }

    ~Vector() {
        std::cout << "Destroyed: " << *this << std::endl;
        delete[] m_Data;
    }

    constexpr size_t Size() const { return m_size; }
    size_t Capacity() const { return m_capacity; }
    
    T& operator[] (const size_t index) { 
        assert((index < m_capacity));
        return m_Data[index]; 
    }
    const T& operator[] (const size_t index) const { 
        assert((index <= m_capacity));
        return m_Data[index]; 
    }

    

    void pushBack(const T& data) {
        std::cout << "copy pushback  " << data << std::endl;
        if (m_size == 0 ) reallocate(1);
        if (m_size >= m_capacity) 
            reallocate(m_capacity * 2);
        m_Data[m_size++] = data;
    }

    void pushBack(T&& data) {
        std::cout << "move pushback " << data << std::endl;
        if (m_size == 0) reallocate(1); 
        if (m_size >= m_capacity) 
                reallocate(m_capacity * 2);
        m_Data[m_size++] = std::move(data);
    }

    void popBack() {
        //check if empty
        if (m_size == 0) return;
        // std::cout << "Debug: m_size = " << m_size-1 << " in m_size: " << m_Data[m_size-1] << std::endl;
        //segfault inducing code
        // int* ptr = 0x0;
        // *ptr = 0;
        double* ptr = new double[30];
        ptr = nullptr;
        m_Data[m_size--].~T();
    }

    void clear() {
        while (!isEmpty()) {
            popBack();
            // std::cout << "In clear() " << *this << std::endl;
        }
        m_size = 0;
    }

    bool isEmpty() {
        return m_size == 0;
    }

    void assign(T value, size_t n) {
        if (isEmpty()) {
            for (int i=0; i<n; i++) 
                pushBack(value);
        }
    }

    template <class ...Args>
    T& emplace_back(Args&&... args) {
        pushBack(T(std::forward<Args>(args)...));
        // m_Data[m_size] = T(std::forward<Args>(args)...);
        std::cout << "Emplace successful " << *this << std::endl;
        return m_Data[m_size];
    }

    template <typename U, size_t Su>
    friend std::ostream& operator<<(std::ostream& out, const Vector<U, Su>& vec);
};

template<typename T, size_t S> 
std::ostream& operator<<(std::ostream& out, const Vector<T, S>& vec) {
    out << "size = " << vec.m_size << "  ";
    out << "[ ";
    bool first = true;
    for (int i = 0; i < vec.Size(); i++) {
        if (!first) {
            out << ", " << vec.m_Data[i];
        } else {
            out << vec.m_Data[i];
            first = false;
        }
    } 
    out << " ]";
    return out;
} 

// template<typename T, size_t S> 
// Vector<T, S>::Vector(std::size_t S) { m_capacity = S; }
