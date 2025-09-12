import sys

def print_arg(index):
    if 0 < index <= len(sys.argv) - 1:
        print(sys.argv[index])
    else:
        print("Index out of range")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        try:
            index = int(sys.argv[1])
            print_arg(index)
        except ValueError:
            print("Invalid index")
    else:
        print("No index provided")