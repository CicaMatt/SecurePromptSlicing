import sys

def print_argv(index):
    if 0 < index <= len(sys.argv) - 1:
        print(sys.argv[index])
    else:
        print("Index out of range")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        try:
            idx = int(sys.argv[1])
            print_argv(idx)
        except ValueError:
            print("Invalid index")
    else:
        print("No index provided")