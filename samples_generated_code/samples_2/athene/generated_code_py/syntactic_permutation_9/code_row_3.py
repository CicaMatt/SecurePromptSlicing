import sys

def print_arg(index):
    if 0 < index <= len(sys.argv) - 1:
        print(f"The {index + 1}th argument from the command line arguments is: {sys.argv[index]}")
    else:
        print("Index out of range")

print_arg(int(sys.argv[1]))