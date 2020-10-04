/*
 *    Project Name : HW1 - Dynamic Array
 *
 *    Written by Kwon, Han Kyul,
 *      School of Electrical and Electronics Engineering
 *      Sungkyunkwan University.
 *
 *    File name: HW_1_1_2016313517.cpp
 *    Program date: 2020.10.03.
 *
 *    Written on Oct 3, 2020
 *    Modified on Oct 3, 2020
 *    Modification History:
 *          1. Written by Han Kyul Kwon
 *          2. Modified by Han Kyul Kwon on June 8, 2017
 *              (a) Add codes for normal execution. (on parctice hours)
 *          3. Modified by Han Kyul Kwon on June 21, 2017
 *              (a) Add comments for explanation.
 *
 *    Language used: C++ 11
 *    Compiler used: G++ 5.4.0
 */

#include <iostream>
#include <chrono>

using namespace std;

template <typename T>
class DynamicArray {
//A dynamic array class akin to a simplified Python list.//
private:
    int n;              // count actual elements
    int capacity;       // default array capacity
    T* A;               // low-level array
public:
    DynamicArray() {
        // Create an empty array. //
        this->n = 0;
        this->capacity = 1;
        this->A = new T[this->capacity];
    }

    ~DynamicArray() {
        delete[] A;
    }

    int len() {
        // Return number of elements stored in the array. //
        return this->n;
    }

    T operator[](int k) {
        // Return element at index k. //
        if (!((0 <= k) && (k < this->n))) {
            cout << "[ERROR] invalid index" << endl;
            return NULL;
        }
        return this->A[k];      // retrieve from array
    }

    void append(T obj) {
        //Add object to end of the array.//
        if (this->n == this->capacity) {             // not enough room
            this->resize(2 * this->capacity);       // so double capacity
        }
        (this->A)[this->n] = obj;
        this->n++;
    }

    void append_incremental(T obj, int c) {
        //Add object to end of the array by incrementing.//
        if (this->n == this->capacity) {
            this->resize(this->capacity + c);
        }
        (this->A)[this->n] = obj;
        this->n++;
    }

    void resize(int c) {                    // nonpublic utitity
        //Resize internal array to capacity c.//
        int* B = new int[c]();
        for (int k = 0; k < this->n; k++) {            // for each existing value
            B[k] = this->A[k];
        }
        delete[] this->A;       // delete old array
        this->A = B;            // use the bigger array
        this->capacity = c;
    }
};

double compute_average_append(int n) {
    //Perform n appends to an empty list//
    DynamicArray<int> data;

    chrono::system_clock::time_point startTime = chrono::system_clock::now();

    for (int k = 0; k < n; k++) {
        data.append(0);
    }

    chrono::duration<double> dur = chrono::system_clock::now() - startTime;

    return dur.count();
}

double compute_average_append_inc(int n, int c) {
    //Perform n appends to an empty list//
    DynamicArray<int> data;

    chrono::system_clock::time_point startTime = chrono::system_clock::now();

    for (int k = 0; k < n; k++) {
        data.append_incremental(0, c);
    }

    chrono::duration<double> dur = chrono::system_clock::now() - startTime;

    return dur.count();
}


int iteration[] = { 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };

int c = 1000000;

int main(void) {
    // dynamic array running time test
    int len_iter = sizeof(iteration) / sizeof(*iteration);
    cout << "**** Dynamic Array Running Time Test ****" << endl << endl;

    cout << scientific;

    cout << "1. Doubling" << endl;

    for (int i = 0; i < len_iter; i++) {
        cout << iteration[i] << ':' << compute_average_append(iteration[i]) << endl;
    }

    cout << endl << "2. Increment" << endl;

    for (int i = 0; i < len_iter; i++) {
        cout << iteration[i] << ':' << compute_average_append_inc(iteration[i], c) << endl;
    }

    return 0;
}