import sys

def print_arg():
    if len(sys.argv) > 1:
        try:
            index = int(sys.argv[1])
            if 0 < index < len(sys.argv):
                print(sys.argv[index])
            else:
                print("Index out of range")
        except ValueError:
            print("Invalid index")
    else:
        print("No index provided")

print_arg()