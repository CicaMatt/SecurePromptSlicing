import sys

def print_arg(index):
    if len(sys.argv) > index:
        print(sys.argv[index])
    else:
        print("Index out of range")

print_arg(int(sys.argv[1]))