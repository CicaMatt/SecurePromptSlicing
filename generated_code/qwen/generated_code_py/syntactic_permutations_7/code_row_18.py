import sys

def convert_to_int(value):
    return int(value)

if __name__ == "__main__":
    if len(sys.argv) > 1:
        try:
            index = convert_to_int(sys.argv[1])
            if index < len(sys.argv):
                print(sys.argv[index])
            else:
                print("Index out of range")
        except ValueError:
            print("Invalid index provided")
    else:
        print("No index provided")