/*
 *    Project : HW1-2 Stack
 *
 *    Written by Kwon, Han Kyul (2016313517),
 *      School of Electrical and Electronics Engineering
 *      Sungkyunkwan University.
 *
 *    File name: HW_1_2_2016313517.cpp
 *    Program date: 2020.10.05.
 *
 *    Written on Oct 3, 2020
 *    Modified on Oct 5, 2020
 *    Modification History:
 *          1. Written by Han Kyul Kwon
 *              (a) Add ArrayStack class.
 *          2. Modified by Han Kyul Kwon on Oct 5, 2020
 *              (a) Add codes for normal execution.
 *              (b) Add comments for explanation.
 *
 *    Language used: C++ 11
 *    Compiler used: G++ 5.4.0
 */

#define MAX_STACK_SIZE 1000     // Maximum stack size

#include <iostream>

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
 * Verify that the text entered by the user is palindrome. 
 * Input:
 *  string user_input: 
 * Output:
 *  Return true if user input text is 
 **/
bool is_palindrome(string user_input) {
    ArrayStack<char> arr_stk;
    int input_len = user_input.length();
    
    for (int i = 0 ; i < input_len ; i++) {
        arr_stk.push(user_input[i]);
    }

    string reversed_input = "";
    
    while (!arr_stk.is_empty()) {
        reversed_input += arr_stk.pop();
    }

    if (user_input == reversed_input) {
        return true;
    } else {
        return false;
    }
}


/**
 * Main function of the program
 *  Get the user input and prints out whether the entered text is palindrome.
 */
int main(void) {
    cout << "*********************************************" << endl;
    cout << "****         Data Structure HW1-2        ****" << endl;
    cout << "****     Name: Kwon Han Kyul             ****" << endl;
    cout << "****     Student ID: 2016313517          ****" << endl;
    cout << "*********************************************" << endl << endl;

    string user_input;

    while (true) {
        cout << "Please input words: ";
        getline(cin, user_input);

        if (is_palindrome(user_input)) {
            cout << user_input << " is palindrome." << endl;
        } else {
            cout << user_input << " is not palindrome." << endl;
        }
        cout << "---------------------------------------------" << endl;
    }
    return 0;
}