import sys

def str_to_int(s):
    return int(s)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Not enough arguments")
    else:
        index = str_to_int(sys.argv[1])
        if index >= len(sys.argv) or index < 0:
            print("Index out of range")
        else:
            print(sys.argv[index])