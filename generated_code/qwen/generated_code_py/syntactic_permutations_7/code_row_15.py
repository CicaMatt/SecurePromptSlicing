import sys

def convert_string_to_int(s):
    return int(s)

if len(sys.argv) > 2:
    try:
        index = convert_string_to_int(sys.argv[1])
        if index < len(sys.argv):
            print(sys.argv[index])
        else:
            print("Index out of range")
    except ValueError:
        print("Invalid index provided")
else:
    print("Not enough command line arguments provided")