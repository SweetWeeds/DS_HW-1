class ArrayQueue:
    """FIFO queue implementation using a Python list as underlying storage."""
    DEFAULT_CAPACITY = 10   # moderate capacity for all new queues
    
    def __init__(self):
        """Create an empty queue."""
        self._data = [None] * ArrayQueue.DEFAULT_CAPACITY
        self._size = 0
        self._front = 0
    
    def __len__(self):
        """Return the number of elements in the queue."""
        return self._size
    
    def is_empty(self):
        """Return True if the queue is_empty."""
        return self._size == 0
    
    def first(self):
        """Return (but do not remove) the element at the front of the queue.
        Raise Empty exception if the queue is_empty.
        """
        if self.is_empty():
            raise Empty('Queue is_empty')
        return self._data[self._front]
    
    def dequeue(self):
        """Remove and return the first element of the queue (i.e., FIFO).
        Raise Empty exception if the queue is_empty.
        """
        if self.is_empty( ):
            raise Empty( 'Queue is_empty' )
        answer = self._data[self._front]
        # help garbage collection
        self._data[self._front] = None
        self._front = (self._front + 1) % len(self._data)
        self._size -= 1
        return answer

    def enqueue(self, e):
        """Add an element to the back of queue."""
        if self._size == len(self._data):
            self._resize(2 * len(self._data))
        avail = (self._front + self._size) % len(self._data)
        self._data[avail] = e
        self._size += 1
    
    def _resize(self, cap):
        """Resize to a new list of capacity >= len(self.)"""
        old = self._data
        self._data = [None] * cap
        walk = self._front
        for k in range(self._size):
            self._data[k] = old[walk]
            walk = (1 + walk) % len(old)
        self._front = 0

class ArrayDequeue(ArrayQueue):
    def add_first(self, e):
        if self._size == len(self._data):
            self._resize(2 * len(self._data))
        self._front = (self._front - 1) % len(self._data)
        avail = self._front
        self._data[avail] = e
        self._size += 1

    def add_last(self, e):
        self.enqueue(e)

    def delete_first(self):
        return self.dequeue()

    def delete_last(self):
        """Remove and return the last element of the queue (i.e., FILO).
        Raise Empty exception if the queue is_empty.
        """
        if self.is_empty( ):
            raise Empty( 'Queue is_empty' )
        
        # find last index of queue
        cur = (self._front + self._size) % len(self._data) - 1
        answer = self._data[cur]
        # help garbage collection
        self._data[cur] = None
        self._size -= 1
        if self._size == len(self._data)/2:
            self._resize(int(len(self._data)/2))
        return answer

    def first(self):
        self.first()

    def last(self):
        """Return (but do not remove) the element at the last of the queue.
        Raise Empty exception if the queue is_empty.
        """
        if self.is_empty():
            raise Empty('Queue is_empty')
        cur = (self._front + self._size) % len(self._data) - 1
        return self._data[cur]
    
    def show(self):
        print("ArrayDeqeue's array:{}".format(self._data))

class Empty(Exception):
    """Error attempting to access from an empty container"""
    pass

""" Palindrome Checker """
def is_palindrome():
    D = ArrayDequeue()
    user_input = input("Please input words:")
    for i in user_input:
        D.add_last(i)
    D.show()
    reversed_input = ""
    for i in range(len(D)):
        reversed_input += D.delete_last()
    
    if user_input == reversed_input:
        print("{} is palindrome".format(user_input))
    else:
        print("{} is not palindrome".format(user_input))

if __name__ == "__main__":
    while(True):
        is_palindrome()