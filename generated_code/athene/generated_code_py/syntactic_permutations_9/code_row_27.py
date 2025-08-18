import sys

def print_arg(index):
    if len(sys.argv) > index:
        print(sys.argv[index])
    else:
        print("Index out of range")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 argv_index.py <index>")
    else:
        try:
            index = int(sys.argv[1])
            print_arg(index)
        except ValueError:
            print("Please provide a valid integer as the index")