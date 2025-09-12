import sys

def argv_index(index):
    try:
        print(sys.argv[index])
    except IndexError:
        print("Index out of range")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        try:
            idx = int(sys.argv[1])
            argv_index(idx)
        except ValueError:
            print("Please provide a valid integer index")
    else:
        print("Usage: python3 argv_index.py <index>")