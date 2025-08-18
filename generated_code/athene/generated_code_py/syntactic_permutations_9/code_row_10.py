import sys

def argv_index(index):
    try:
        print(sys.argv[index])
    except IndexError:
        print("Not enough arguments provided.")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        index = int(sys.argv[1])
        argv_index(index)
    else:
        print("Usage: python3 argv_index.py <index>")