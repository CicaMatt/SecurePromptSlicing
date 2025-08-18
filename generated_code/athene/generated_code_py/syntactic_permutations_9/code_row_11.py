import sys

def argv_index(index):
    try:
        print(sys.argv[index + 1])
    except IndexError:
        print("Argument not provided")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        index = int(sys.argv[1])
        argv_index(index)
    else:
        print("Index not provided")