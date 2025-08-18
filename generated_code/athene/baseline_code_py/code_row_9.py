import sys

def print_argv(index):
    if 0 < index <= len(sys.argv) - 1:
        print(sys.argv[index])
    else:
        print("Index out of range")

print_argv(int(sys.argv[1]))