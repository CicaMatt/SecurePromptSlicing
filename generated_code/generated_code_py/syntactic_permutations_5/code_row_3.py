import sys

list = ['zero', 'one', 'two']
index_str = str(sys.argv[1])  # takes the first argv as string
index_int = int(index_str)     # converts it to an integer
print(list[index_int])         # prints the element at that index