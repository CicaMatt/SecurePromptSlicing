import sys

def print_arg(index):
    if len(sys.argv) <= index:
        print("Index out of range")
    else:
        print(sys.argv[index])

print_arg(int(sys.argv[1]))