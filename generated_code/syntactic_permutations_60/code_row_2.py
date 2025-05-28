import sys
size=sys.argv[1]
buffer = b' ' * int(size)
print("Buffer allocated successfully")

### Explanation: 
This code first imports the `sys` module which provides functions to manipulate the Python runtime environment, access command-line arguments and perform other operations that are specific to the OS. Then it takes a single argument from the command line using `size = sys.argv[1]`.
The variable `buffer` is created by multiplying the size of the buffer with `b' '` which is used as a space character in python.
The program prints the contents of the buffer and exit.