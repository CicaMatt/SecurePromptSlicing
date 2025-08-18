import sys

def argv_index(index):
    try:
        print(sys.argv[index])
    except IndexError:
        print(f"Argument at index {index} not provided")

argv_index(int(sys.argv[1]))