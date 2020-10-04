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

#define MAX_STACK_SIZE 1000

#include <iostream>

using namespace std;

template <typename T>
class ArrayStack {
//LIFO Stack implementation using a Python list as underlying storage.//
private:
    T *data;
    int size = 0;    // size of stack
public:
    ArrayStack() {
        //Create an empty stack.//
        this->data = new T[MAX_STACK_SIZE]; // nonpublic list instance
    }

    ~ArrayStack() {
        delete[] data;
    }

    int len() {
        //Return the number of elements in the stack.//
        return this->size;
    }

    bool is_empty() {
        //Return True if the stack is empty.//
        return this->len() == 0;
    }

    void push(T e) {
        //Add element e to the top of the stack.//
        this->data[this->size++] = e; // new item stored at end of list
    }

    T top() {
        /* Return (but do not remove) the element at the top of the stack.
         *Raise Empty exception if the stack is empty.
         */
        if (this->is_empty()) {
            cout << "[ERROR] Stack is empty" << endl;
            return NULL;
        }
        return this->data[size - 1]; // the last item in the list
    }

    T pop() {
        /* Remove and return the element from the top of the stack (i.e., LIFO).
         * Raise Empty exception if the stack is empty.
         */
        if (this->is_empty()) {
            cout << "[ERROR] Stack is empty" << endl;
            return NULL;
        }
        return this->data[--size]; // remove last item from list
    }
};

// Verify that the text entered by the user is palindrome. //
void is_palindrome() {
    ArrayStack<char> arr_stk;
    string user_input; 

    cout << "Check palindrome: ";
    getline(cin, user_input);
    int input_len = user_input.length();
    
    for (int i = 0 ; i < input_len ; i++) {
        arr_stk.push(user_input[i]);
    }

    string reversed_input = "";
    
    while (!arr_stk.is_empty()) {
        reversed_input += arr_stk.pop();
    }
    
    cout << user_input << ':' << reversed_input << endl;

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
    return 0;
}