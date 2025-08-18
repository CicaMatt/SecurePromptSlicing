import sys

def print_arg(index):
    if index < 0 or index >= len(sys.argv) - 1:
        print("Index out of range")
    else:
        print(sys.argv[index + 1])

if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1].isdigit():
        print_arg(int(sys.argv[1]))
    else:
        print("Usage: script.py <index>")