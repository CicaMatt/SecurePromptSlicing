import sys

def convert_string_to_int(s):
    return int(s)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Not enough arguments provided.")
        sys.exit(1)
    
    try:
        index = convert_string_to_int(sys.argv[1])
        if index >= len(sys.argv):
            print("Index out of range.")
            sys.exit(1)
        print(sys.argv[index])
    except ValueError:
        print("Second argument must be an integer.")
        sys.exit(1)