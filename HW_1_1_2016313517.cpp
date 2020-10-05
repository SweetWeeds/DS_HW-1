/*
 *    Project : HW1-1 Dynamic Array
 *
 *    Written by Kwon, Han Kyul (2016313517),
 *      School of Electrical and Electronics Engineering
 *      Sungkyunkwan University.
 *
 *    File name: HW_1_1_2016313517.cpp
 *    Program date: 2020.10.05.
 *
 *    Written on Oct 3, 2020
 *    Modified on Oct 5, 2020
 *    Modification History:
 *          1. Written by Han Kyul Kwon
 *              (a) Add DynamicArray class.
 *              (b) Add codes for comparing append method.
 *          2. Modified by Han Kyul Kwon on Oct 05, 2020.
 *              (a) Add comments for explanation.
 *
 *    Language used: C++ 11
 *    Compiler used: G++ 5.4.0
 */

#include <iostream>
#include <chrono>

using namespace std;

/**
 * A dynamic array class akin to a simplified Python list.
 */
template <typename T>
class DynamicArray {
private:
    int n;              // count actual elements
    int capacity;       // default array capacity
    T* A;               // low-level array

    /** 
     * Resize internal array to capacity c.
     * nonpublic utitity.
     */
    void resize(int c) {
        int* B = new int[c]();
        for (int k = 0; k < this->n; k++) {
            B[k] = this->A[k];
        }
        delete[] this->A;       // delete old array
        this->A = B;            // use the bigger array
        this->capacity = c;     // new capacity
    }
public:
    /**
     * Constructor
     * Create an empty array.
     */
    DynamicArray() {
        this->n = 0;
        this->capacity = 1;
        this->A = new T[this->capacity];
    }

    /**
     * Destructor
     */
    ~DynamicArray() {
        delete[] A;
    }

    /**
     * Return number of elements stored in the array.
     */
    int len() {
        return this->n;
    }

    /**
     * Return element at index k.
     */
    T operator[](int k) {
        if (!((0 <= k) && (k < this->n))) {
            cout << "[ERROR] invalid index" << endl;
            return NULL;
        }
        return this->A[k];      // retrieve from array
    }

    /** 
     * Add object to end of the array.
     */
    void append(T obj) {
        if (this->n == this->capacity) {            // not enough room
            this->resize(2 * this->capacity);       // so double capacity
        }
        (this->A)[this->n] = obj;
        this->n++;
    }

    /**
     * Add object to end of the array by incrementing.
     */
    void append_incremental(T obj, int c) {
        if (this->n == this->capacity) {
            this->resize(this->capacity + c);
        }
        (this->A)[this->n] = obj;
        this->n++;
    }
};


/**
 * Perform n appends to an empty list
 * return:
 *  time spent on append
 */
double compute_average_append(int n) {
    
    DynamicArray<int> data;

    // Get start time.
    chrono::system_clock::time_point startTime = chrono::system_clock::now();

    for (int k = 0; k < n; k++) {
        data.append(0);
    }

    // Calculate duration.
    chrono::duration<double> dur = chrono::system_clock::now() - startTime;

    return dur.count();
}


/**
 * Perform n appends to an empty list with 'append_incremental' method.
 * return:
 *  time spent on append
 */
double compute_average_append_inc(int n, int c) {
    DynamicArray<int> data;

    chrono::system_clock::time_point startTime = chrono::system_clock::now();

    for (int k = 0; k < n; k++) {
        data.append_incremental(0, c);
    }

    chrono::duration<double> dur = chrono::system_clock::now() - startTime;

    return dur.count();
}


/**
 * Main function of the program
 *  Test the running time of dynamic array.
 */
int main(void) {
    // Test array sizes.
    int iteration[] = {100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    int c = 1000000;    // Increment parameter
    int len_iter = sizeof(iteration) / sizeof(*iteration);
    
    cout << "*********************************************" << endl;
    cout << "****         Data Structure HW1-1        ****" << endl;
    cout << "****    Student Name: Kwon Han Kyul      ****" << endl;
    cout << "****    Student ID: 2016313517           ****" << endl;
    cout << "*********************************************" << endl << endl;

    cout << scientific;     // Settings for decimal representation

    cout << "1. Doubling" << endl;

    for (int i = 0; i < len_iter; i++) {
        cout << iteration[i] << ':'
        << compute_average_append(iteration[i]) << endl;
    }

    cout << endl << "2. Increment (c: " << c << ")" << endl;
    for (int i = 0; i < len_iter; i++) {
        cout << iteration[i] << ':'
        << compute_average_append_inc(iteration[i], c) << endl;
    }

    return 0;
}