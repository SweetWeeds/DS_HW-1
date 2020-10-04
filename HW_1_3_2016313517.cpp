/*
 *    Programming Lab. : Dynamic Array
 *
 *    Written by Kwon, Han Kyul,
 *      School of Electrical and Electronics Engineering
 *      Sungkyunkwan University.
 *
 *    File name: HW_1_2_2016313517.cpp
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

using namespace std;

#define DEFAULT_CAPACITY 10   // moderate capacity for all new queues

template <typename T>
class ArrayQueue {
//FIFO queue implementation using a Python list as underlying storage.//
private:
    int size;
    int front;
    int cap;
    T *data;
public:
    ArrayQueue() {
        //Create an empty queue.//
        this->data = new T[DEFAULT_CAPACITY];
        this->size = 0;
        this->front = 0;
        this->cap = DEFAULT_CAPACITY;
    }

    ~ArrayQueue() {
        delete[] this->data;
    }

    int len() {
        //Return the number of elements in the queue.//
        return this->size;
    }
    
    bool is_empty() {
        //Return True if the queue is_empty.//
        return this->size == 0;
    }
    
    T first() {
        /* Return (but do not remove) the element at the front of the queue.
         *Raise Empty exception if the queue is_empty.
         */
        if (this->is_empty()) {
            cout << "[ERROR] Queue is_empty" << endl;
            return NULL;
        }
        return this->data[this->front];
    }
    
    T dequeue() {
        /* Remove and return the first element of the queue (i.e., FIFO).
         * Raise Empty exception if the queue is_empty.
         */
        if (this->is_empty()) {
            cout << "[ERROR] Queue is_empty" << endl;
            return NULL;
        }
        
        T answer = this->data[this->front];
        // help garbage collection
        this->data[this->front] = NULL;
        this->front = (this->front + 1) % (sizeof(this->data) / sizeof(T));
        this->size--;
        return answer;
    }

    void enqueue(T e) {
        //Add an element to the back of queue.//
        if (this->size == len(this->data)) {
            this->resize(2 * len(this->data));
        }
        int avail = (this->front + this->size) % len(this->data);
        this->data[avail] = e;
        this->size++;
    }
    
    void resize(int cap) {
        // Resize to a new list of capacity >= len(.) //
        T old[] = new T[this->cap];
        memcpy(old, this->data, sizeof(this->data));
        delete[] this->data;
        this->data = new T[cap];
        this->cap = cap;
        int walk = this->front;
        for (int k = 0 ; k < this->size ; k++) {
            this->data[k] = old[walk];
            walk = (1 + walk) % len(old);
        }
        delete[] old;
        this->front = 0;
    }
};

template <typename U>
class ArrayDequeue : public ArrayQueue<U> {
public:
    void add_first(U e) {
        if (this->size == len(this->data)) {
            this->resize(2 * len(this->data));
        }
        this->front = (this->front - 1) % len(this->data);
        int avail = this->front;
        this->data[avail] = e;
        this->size++;
    }

    void add_last(U e) {
        this->enqueue(e);
    }

    U delete_first() {
        return this->dequeue();
    }

    U delete_last() {
        /* Remove and return the last element of the queue (i.e., FILO).
         * Raise Empty exception if the queue is_empty.
         */
        if (this->is_empty()) {
            cout << "[ERROR] Queue is_empty" << endl;
            return NULL;
        }
        
        // find last index of queue
        int cur = (this->front + this->size) % len(this->data) - 1;
        U answer = this->data[cur];
        // help garbage collection
        this->data[cur] = NULL;
        this->size--;
        if ((0 < this->size) && (this->size < len(this->data) / 4)) {
            this->resize(len(this->data) / 2);
        }
        return answer;
    }

    U last() {
        /* Return (but do not remove) the element at the last of the queue.
         * Raise Empty exception if the queue is_empty.
         */
        if (this->is_empty()) {
            cout << "[ERROR] Queue is_empty" << endl;
            return NULL;
        }

        int cur = (this->front + this->size) % len(this->data) - 1;
        
        return this->data[cur];
    }

};

// Palindrome Checker //
void is_palindrome() {
    ArrayDequeue<char> D;
    string user_input;
    cout << "Please input words: ";
    getline(cin, user_input);
    int input_len = user_input.length();
    
    for (int i = 0 ; i < input_len ; i++) {
        D.add_last(user_input[i]);
    }
    
    string reversed_input = "";

    for (int i = 0 ; i < D.len() ; i++) {
        reversed_input += D.delete_last();
    }
    
    if (user_input == reversed_input) {
        cout << user_input << " is palindrome." << endl;
    } else {
        cout << user_input << " is not palindrome." << endl;
    }
}

int main(void) {
    while(1) {
        is_palindrome();
    }
}