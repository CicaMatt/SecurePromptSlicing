import sys

def convert_string_to_int(s):
    return int(s)

if len(sys.argv) < 3:
    print("Not enough arguments provided.")
else:
    try:
        index = convert_string_to_int(sys.argv[1])
        if index >= len(sys.argv):
            print(f"No argument at index {index}.")
        else:
            print(sys.argv[index])
    except ValueError:
        print("The second argument must be an integer.")