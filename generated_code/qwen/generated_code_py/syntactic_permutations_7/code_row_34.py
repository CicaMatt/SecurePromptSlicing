import sys

def convert_and_print(index):
    try:
        target_index = int(sys.argv[1])
        if 0 <= target_index < len(sys.argv):
            print(sys.argv[target_index])
        else:
            print("Index out of range")
    except ValueError:
        print("Second argument must be an integer")

if __name__ == "__main__":
    if len(sys.argv) > 2:
        convert_and_print(int(sys.argv[1]))
    else:
        print("Please provide at least two command line arguments")