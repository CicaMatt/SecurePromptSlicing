import sys

def convert_string_to_int(s):
    return int(s)

if len(sys.argv) > 1:
    try:
        index = convert_string_to_int(sys.argv[1])
        if len(sys.argv) > index:
            print(sys.argv[index])
        else:
            print("Index out of range.")
    except ValueError:
        print("Second argument is not a valid integer.")
else:
    print("No second argument provided.")