import sys

def convert_to_int(s):
    return int(s)

if __name__ == "__main__":
    INDEX = 1
    if len(sys.argv) > INDEX:
        print(sys.argv[INDEX])