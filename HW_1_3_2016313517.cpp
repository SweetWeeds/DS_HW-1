/*
 *    Project : HW1-3 Queue
 *
 *    Written by Kwon, Han Kyul (2016313517),
 *      School of Electrical and Electronics Engineering
 *      Sungkyunkwan University.
 *
 *    File name: HW_1_3_2016313517.cpp
 *    Program date: 2020.10.05.
 *
 *    Written on Oct 3, 2020
 *    Modified on Oct 5, 2020
 *    Modification History:
 *          1. Written by Han Kyul Kwon
 *              (a) Add ArrayQueue class based on Python example code.
 *          2. Modified by Han Kyul Kwon on Oct 04, 2020
 *              (a) Add ArrayDeque class which inherits ArrayQueue.
 *          3. Modified by Han Kyul Kwon on Oct 05, 2020
 *              (a) Add palindrome check function. (bool is_palindrome())
 *              (b) Add comments for explanation.
 *
 *    Language used: C++ 11
 *    Compiler used: G++ 5.4.0
 */
#define MAX_STACK_SIZE 1000     // Maximum stack size
#define DEFAULT_CAPACITY 10     // moderate capacity for all new queues

#include <iostream>
#include <cstring>
#include <chrono>

using namespace std;

/**
 * LIFO Stack implementation using a Python list as underlying storage.
 */
template <typename T>
class ArrayStack {
private:
    T *data;
    int size = 0;    // size of stack
public:
    /** 
     * Constructor 
     * Create an empty stack.
     */
    ArrayStack() {
        this->data = new T[MAX_STACK_SIZE]; // nonpublic list instance
    }

    /**
     * Destructor
     */
    ~ArrayStack() {
        delete[] data;
    }

    /** 
     * Return the number of elements in the stack.
     */
    int len() {
        return this->size;
    }

    /**
     * Return True if the stack is empty.
     */
    bool is_empty() {
        return this->len() == 0;
    }

    /**
     * Add element e to the top of the stack.
     */
    void push(T e) {
        this->data[this->size++] = e; // new item stored at end of list
    }
    
    /**
     * Return (but do not remove) the element at the top of the stack.
     * Raise Empty exception if the stack is empty.
     */
    T top() {

        if (this->is_empty()) {
            cout << "[ERROR] Stack is empty" << endl;
            return NULL;
        }
        return this->data[size - 1]; // the last item in the list
    }

    /**
     * Remove and return the element from the top of the stack (i.e., LIFO).
     * Raise Empty exception if the stack is empty.
     */
    T pop() {
        if (this->is_empty()) {
            cout << "[ERROR] Stack is empty" << endl;
            return NULL;
        }
        return this->data[--size]; // remove last item from list
    }
};


/**
 * FIFO queue implementation using a array as underlying storage.
 */
template <typename T>
class ArrayQueue {
protected:
    int size;       // current size of stack
    int front;      // stack's front index
    int cap;        // capacity of stack
    T *data;        // stack's array
    
    /**
     * Resize the new array of capacity
     * Input:
     *  int cap: new capacity for queue.
     */
    void resize(int cap) {
        // Save the array's data temporarily.
        T *old = new T[this->cap];
        memcpy(old, this->data, this->cap * sizeof(T));

        delete[] this->data;
        this->data = new T[cap];

        // Copy data to extended memory.
        int walk = this->front;
        for (int k = 0 ; k < this->size ; k++) {
            this->data[k] = old[walk];
            walk = (1 + walk) % this->cap;
        }
        this->cap = cap;
        delete[] old;
        this->front = 0;
    }
public:
    /**
     * Constructor
     * Create an empty queue.
     */
    ArrayQueue() {
        this->cap = DEFAULT_CAPACITY;
        this->data = new T[this->cap];
        this->size = 0;
        this->front = 0;
    }

    /**
     * Destructor
     */
    ~ArrayQueue() {
        delete[] this->data;
    }

    /**
     * Return the number of elements in the queue.
     * Output:
     *  number of elements in the queue.
     */
    int len() {
        return this->size;
    }

    /**
     * Return True if the queue is_empty.
     * Output:
     *  whether this queue is empty.
     */
    bool is_empty() {
        return this->size == 0;
    }

    /**
     * Return (but do not remove) the element at the front of the queue.
     * Raise Empty exception if the queue is_empty.
     * Output:
     *  Return first element of the queue.
     *  If queue is empty, return NULL.
     */
    T first() {
        if (this->is_empty()) {
            cout << "[ERROR] Queue is_empty" << endl;
            return NULL;
        }
        return this->data[this->front];
    }
    
    /**
     * Remove and return the first element of the queue (i.e., FIFO).
     * Raise Empty exception if the queue is_empty.
     * Output:
     *  Return first element of the queue.
     *  If queue is empty, return NULL.
     */
    T dequeue() {
        if (this->is_empty()) {
            cout << "[ERROR] Queue is_empty" << endl;
            return NULL;
        }
        
        T answer = this->data[this->front];
        this->data[this->front] = NULL;
        this->front = (this->front + 1) % this->cap;
        (this->size)--;
        return answer;
    }

    /**
     * Add an element to the back of queue.
     * Input:
     *  T e: element which you want to add in rear of queue.
     */
    void enqueue(T e) {
        if (this->size == this->cap - 1)
            this->resize(2 * this->cap);

        int avail = (this->front + this->size) % this->cap;
        this->data[avail] = e;
        (this->size)++;
    }
};


/**
 * A queue-like data structure that supports insertion and
 *  deletion at both the front and the back of the queue.
 */
template <typename U>
class ArrayDequeue : public ArrayQueue<U> {
public:
    /**
     * Add element to the front of dequeue.
     * Input:
     *  U e: element which you want to add to the data array(this->data).
     */
    void add_first(U e) {
        // Resize if current size is full.
        if (this->size == this->cap - 1)
            this->resize(2 * this->cap);
        
        // Get new front index of dequeue.
        this->front = (this->front - 1) % this->cap;
        int avail = this->front;
        this->data[avail] = e;
        (this->size)++;
    }

    /**
     * Add element to the back of deque.
     * Output:
     *  equivalent method of parent class.
     */
    void add_last(U e) {
        this->enqueue(e);
    }

    /**
     * Remove and return the first element from deque.
     * An error occurs if the deque is empty.
     * Output:
     *  equivalent method of parent class.
     */
    U delete_first() {
        return this->dequeue();
    }

    /**
     * Remove and return the last element from dequeue.
     * An error occurs if the deque is empty.
     * Output:
     *  U answer: Last element in queue.
     */
    U delete_last() {
        if (this->is_empty()) {
            cout << "[ERROR] Queue is_empty" << endl;
            return NULL;
        }
        
        // find last index of queue
        int cur = (this->front + this->size) % this->cap - 1;
        U answer = this->data[cur];

        this->data[cur] = NULL;
        (this->size)--;

        // Resize if current size is less than 1/4 of capacity
        if ((0 < this->size) && (this->size < (this->cap / 4)))
            this->resize(this->cap / 2);

        return answer;
    }

    /**
     * Return (but do not remove) the element at the last of the queue.
     * Raise Empty exception if the queue is_empty.
     * Output:
     *  U this->data[cur]: Last element in queue.
     */
    U last() {
        if (this->is_empty()) {
            cout << "[ERROR] Queue is_empty" << endl;
            return NULL;
        }

        // find last index of queue
        int cur = (this->front + this->size) % this->cap - 1;
        
        return this->data[cur];
    }
};

/** 
 * Get the user input and prints out whether the entered text is palindrome.
 *
 * Input:
 * Return: 'true' if user input text is palindrome.
 *         'false' if user input text is not palindrome.
 */
bool is_palindrome_dequeue(string user_input) {
    ArrayDequeue<char> D;

    int input_len = user_input.length();
    
    // Add characters to the queue in order.
    for (int i = 0 ; i < input_len ; i++)
        D.add_last(user_input[i]);

    string reversed_input = "";

    // Get queue's data in FILO order.
    for (int i = 0 ; i < input_len ; i++)
        reversed_input += D.delete_last();

    // Check whether the user input text is palindrome.
    if (user_input == reversed_input) {
        return true;
    } else {
        return false;
    }
}

/** 
 * Get the user input and prints out whether the entered text is palindrome.
 *
 * Input:
 * Return: 'true' if user input text is palindrome.
 *         'false' if user input text is not palindrome.
 */
bool is_palindrome_stack(string user_input) {
    ArrayStack<char> S;

    int input_len = user_input.length();
    
    // Add characters to the stack in order.
    for (int i = 0 ; i < input_len ; i++) {
        S.push(user_input[i]);
    }

    string reversed_input = "";
    
    // Get stack's data in FILO order.
    while (!S.is_empty()) {
        reversed_input += S.pop();
    }

    // Check whether the user input text is palindrome.
    if (user_input == reversed_input) {
        return true;
    } else {
        return false;
    }
}


/**
 * Main function of the program
 *  Comparing running time in palindrome test between dequeue and stack.
 */
int main(void) {
    cout << "*********************************************" << endl;
    cout << "****         Data Structure HW1-3        ****" << endl;
    cout << "****     Student Name: Kwon Han Kyul     ****" << endl;
    cout << "****     Student ID: 2016313517          ****" << endl;
    cout << "*********************************************" << endl << endl;

    cout << scientific;     // Settings for decimal representation

    string user_input;                          // User input text
    chrono::system_clock::time_point startTime; // Start time point
    chrono::duration<double> dur;               // Duration of execution

    while (true) {
        cout << "Please input words: ";
        getline(cin, user_input);

        // 1. Dequeue based palindrome test //
        // ------ START ------- //
        cout << "1. Dequeue Based Palindrome Test" << endl;
        startTime = chrono::system_clock::now();
        if (is_palindrome_dequeue(user_input)) {
            cout << user_input << " is palindrome." << endl;
        } else {
            cout << user_input << " is not palindrome." << endl;
        }
        dur = chrono::system_clock::now() - startTime;
        cout << "Time: " << dur.count() << endl << endl;
        // ------- END -------- //

        // 2. Stack based palindrome test //
        // ------ START ------- //
        cout << "2. Stack Based Palindrome Test" << endl;
        startTime = chrono::system_clock::now();
        if (is_palindrome_stack(user_input)) {
            cout << user_input << " is palindrome." << endl;
        } else {
            cout << user_input << " is not palindrome." << endl;
        }
        dur = chrono::system_clock::now() - startTime;
        cout << "Time: " << dur.count() << endl;
        // ------- END -------- //

        cout << "---------------------------------------------" << endl;
    }

    return 0;
}