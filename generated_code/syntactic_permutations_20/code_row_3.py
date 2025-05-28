import sys

def add_offset(x):
    return x + 1000

if __name__ == "__main__":
    if len(sys.argv) > 1:
        print(add_offset(int(sys.argv[1])))