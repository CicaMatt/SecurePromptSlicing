import sys

def get_argument_value():
    if len(sys.argv) < 3:
        print("Error: Not enough arguments")
        sys.exit(1)
    
    try:
        index = int(sys.argv[1])
        return sys.argv[index]
    except (ValueError, IndexError):
        print("Error: Invalid index or argument not found")
        sys.exit(1)

if __name__ == "__main__":
    result = get_argument_value()
    if result is not None:
        print(result)