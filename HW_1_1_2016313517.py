"""
 *    Programming Lab. : Dynamic Array
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

import ctypes # provides low-level arrays
from time import time

class DynamicArray:
    """A dynamic array class akin to a simplified Python list."""
    
    def __init__ (self):
        """Create an empty array."""
        self._n = 0                                 # count actual elements
        self._capacity = 1                          # default array capacity
        self._A = self._make_array(self._capacity)  # low-level array

    def __len__ (self):
        """Return number of elements stored in the array."""
        return self._n

    def __getitem__ (self, k):
        """Return element at index k."""
        if not 0 <= k < self._n:
            raise IndexError('invalid index')
        return self._A[k]                       # retrieve from array

    def append(self, obj):
        """Add object to end of the array."""
        if self._n == self._capacity:            # not enough room
            self._resize(2 * self._capacity)    # so double capacity
        self._A[self._n] = obj
        self._n += 1
        

    def append_incremental(self, obj, c):
        """Add object to end of the array by incrementing."""
        if self._n == self._capacity:
            self._resize(self._capacity + c)
            #print("SIZE:{}".format(self._n))
        self._A[self._n] = obj
        self._n += 1


    def _resize(self, c):                    # nonpublic utitity
        """Resize internal array to capacity c."""
        B = self._make_array(c)             # new (bigger) array
        for k in range(self._n):            # for each existing value
            B[k] = self._A[k]
        self._A = B                         # use the bigger array
        self._capacity = c

    def _make_array(self, c):                # nonpublic utitity
        """Return new array with capacity c."""
        return (c * ctypes.py_object)( )    # see ctypes documentation

def compute_average_append(n):
    """Perform n appends to an empty list"""
    #data = []
    data = DynamicArray()
    start = time()
    for k in range(n):
        data.append(None)
    end = time()
    return (end - start) / n

def compute_average_append_inc(n, c):
    """Perform n appends to an empty list"""
    data = DynamicArray()
    start = time()
    for k in range(n):
        data.append_incremental(None, c)
    end = time()
    return (end - start) / n


iteration = [100, 1000, 10000, 100000, 1000000, 10000000, 100000000]

c = 1000000

if __name__=="__main__":
    print("**** Dynamic Array Running Time Test ****\n\n")
    print("1. Doubling")
    for i in iteration:
        print("{}:{}".format(i, compute_average_append(i)))
    
    print("\n2. Doubling")
    for i in iteration:
        print("{}:{}".format(i, compute_average_append_inc(i, c)))
    
