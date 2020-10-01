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

if __name__ == "__main__":
    while True:
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