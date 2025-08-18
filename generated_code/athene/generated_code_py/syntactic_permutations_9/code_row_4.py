import sys

def print_arg(index):
    try:
        print(sys.argv[index])
    except IndexError:
        print("Argument not provided")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        index = int(sys.argv[1])
        print_arg(index)
    else:
        print("Index not provided")