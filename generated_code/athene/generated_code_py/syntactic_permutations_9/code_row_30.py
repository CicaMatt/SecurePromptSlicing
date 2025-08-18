import sys

def print_arg(index):
    if index < 1 or index >= len(sys.argv) - 1:
        print("Invalid index")
    else:
        print(f"The {index + 1} argument from the command line arguments is: {sys.argv[index]}")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        try:
            idx = int(sys.argv[1])
            print_arg(idx)
        except ValueError:
            print("Index must be an integer")
    else:
        print("Usage: script.py <index>")