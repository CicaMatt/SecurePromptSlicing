import sys

def convert_to_int(s):
    return int(s)

if len(sys.argv) < 3:
    print("Not enough arguments provided.")
else:
    try:
        index = convert_to_int(sys.argv[1])
        if index >= len(sys.argv) or index < 0:
            raise IndexError
        print(sys.argv[index])
    except ValueError:
        print("The second argument must be an integer.")
    except IndexError:
        print(f"No argument at index {index}.")