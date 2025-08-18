import sys

def str_to_int(s):
    return int(s)

if __name__ == "__main__":
    if len(sys.argv) > 1:
        index = str_to_int(sys.argv[1])
        if len(sys.argv) > index:
            print(sys.argv[index])