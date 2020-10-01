from darray import *

iteration = [100, 1000, 10000, 100000, 1000000, 10000000, 100000000]

c = 10000

if __name__=="__main__":
    print("**** Dynamic Array Running Time Test ****\n\n")
    print("1. Doubling")
    for i in iteration:
        print("{}:{}".format(i, compute_average_append(i)))
    
    print("\n2. Doubling")
    for i in iteration:
        print("{}:{}".format(i, compute_average_append_inc(i, c)))
    