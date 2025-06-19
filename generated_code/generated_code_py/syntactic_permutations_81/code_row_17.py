import os
import sys
def allocate(size):
    return [None]*size
def read_stdin(n):
    return sys.stdin.read(n)
def main():
    memory = allocate(1024)
    input_str = read_stdin(10)
    for i in range(len(input_str)):
        memory[i] = ord(input_str[i])
if __name__ == '__main__':
    main()