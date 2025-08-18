import sys

def convert_and_print(index):
    if 0 <= index < len(sys.argv):
        print(sys.argv[index])
    else:
        print("Index out of range")

if __name__ == "__main__":
    try:
        index = int(sys.argv[1])
        convert_and_print(index)
    except IndexError:
        print("Not enough arguments provided")
    except ValueError:
        print("Invalid index value")