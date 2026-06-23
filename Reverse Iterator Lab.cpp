#include <iostream>
#include <cassert>

class vec {
private:
    int* arr;
    int arr_size;
    int arr_capacity;

public:
    class iterator {
    private:
        int* ptr;

    public:
        iterator(int* p) : ptr(p) {}

        int& operator*() {
            return *ptr;
        }

        iterator operator+(int other) {
            return iterator(ptr + other);
        }

        void operator+=(int other) {
            ptr += other;
        }

        iterator operator++() {
            return iterator(ptr++);
        }

        iterator operator++(int) {
            return iterator(ptr++);
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
    };

    class reverse_iterator {
    private:
        int* ptr;

    public:
        reverse_iterator(int* p) : ptr(p) {}

        int& operator*() const {
            return *(ptr - 1);
        }

        int& operator[](int index) const {
            return *(ptr - 1 - index);
        }

        reverse_iterator& operator++() {
            ptr--;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator temp = *this;
            ptr--;
            return temp;
        }

        reverse_iterator& operator--() {
            ptr++;
            return *this;
        }

        reverse_iterator operator--(int) {
            reverse_iterator temp = *this;
            ptr++;
            return temp;
        }

        reverse_iterator operator+(int offset) const {
            return reverse_iterator(ptr - offset);
        }

        reverse_iterator operator-(int offset) const {
            return reverse_iterator(ptr + offset);
        }

        bool operator==(const reverse_iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const reverse_iterator& other) const {
            return ptr != other.ptr;
        }
    };

    iterator begin() {
        return iterator(arr);
    }

    iterator end() {
        return iterator(arr + arr_size);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(arr + arr_size);
    }

    reverse_iterator rend() {
        return reverse_iterator(arr);
    }

    vec() {
        arr = nullptr;
        arr_size = 0;
        arr_capacity = 0;
    }

    vec(int size) {
        if (size == 0) {
            arr = nullptr;
        } else {
            arr = new int[size];
        }
        arr_size = size;
        arr_capacity = size;
    }

    ~vec() {
        delete[] arr;
    }

    int size() {
        return arr_size;
    }

    int capacity() {
        return arr_capacity;
    }

    int& at(int idx) {
        return arr[idx];
    }

    int& operator[](int idx) {
        return arr[idx];
    }

    void push_back(int x) {
        if (arr_size < arr_capacity) {
            arr[arr_size] = x;
            arr_size++;
        } else {
            if (arr_capacity == 0) {
                arr_capacity = 1;
            } else {
                arr_capacity *= 2;
            }

            int* new_arr = new int[arr_capacity];
            for (int i = 0; i < arr_size; i++) {
                new_arr[i] = arr[i];
            }
            new_arr[arr_size] = x;
            delete[] arr;
            arr = new_arr;
            arr_size++;
        }
    }

    int pop_back() {
        if (arr_size == 0) {
            std::cout << "ERROR: cannot pop from empty vector!" << std::endl;
            return -1;
        }
        arr_size--;
        return arr[arr_size];
    }
};

int main() {
    vec v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    vec::reverse_iterator rit = v.rbegin();
    assert(*rit == 40);
    assert(rit[1] == 30);
    assert(rit[3] == 10);

    assert(*(++rit) == 30);
    assert(*(rit++) == 30);
    assert(*rit == 20);

    vec::reverse_iterator offsetTest = v.rbegin() + 2;
    assert(*offsetTest == 20);

    offsetTest = offsetTest - 1;
    assert(*offsetTest == 30);

    for (vec::reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
   