"""
 *    Programming Lab. : Stack
 *
 *    Written by Kwon, Han Kyul,
 *      School of Electrical and Electronics Engineering
 *      Sungkyunkwan University.
 *
 *    File name: HW_1_2_2016313517.py
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
 * Interpreter used: Python 3.8.5
 *
"""

class ArrayStack:
    """LIFO Stack implementation using a Python list as underlying storage."""
    def __init__(self):
        """Create an empty stack."""
        self._data = [ ] # nonpublic list instance
    
    def __len__(self):
        """Return the number of elements in the stack."""
        return len(self._data)

    def is_empty(self):
        """Return True if the stack is empty."""
        return len(self._data) == 0

    def push(self, e):
        """Add element e to the top of the stack."""
        self._data.append(e) # new item stored at end of list

    def top(self):
        """Return (but do not remove) the element at the top of the stack.

        Raise Empty exception if the stack is empty.
        """
        if self.is_empty( ):
            raise Empty('Stack is empty')
        return self._data[-1] # the last item in the list

    def pop(self):
        """Remove and return the element from the top of the stack (i.e., LIFO).

        Raise Empty exception if the stack is empty.
        """
        if self.is_empty( ):
            raise Empty('Stack is empty')
        return self._data.pop() # remove last item from list

class Empty(Exception):
    """Error attempting to access from an empty container"""
    pass

"""Verify that the text entered by the user is palindrome."""
def is_palindrome():
    arr_stk = ArrayStack()
    user_input = input("Check palindrome: ")
    
    for i in user_input:
        arr_stk.push(i)
    
    reversed_input = ""
    
    while not arr_stk.is_empty():
        reversed_input += arr_stk.pop()
    
    if reversed_input == user_input:
        print("{} is palindrome.".format(user_input))
    else:
        print("{} is not palindrome.".format(user_input))

if __name__ == "__main__":
    while True:
        is_palindrome()