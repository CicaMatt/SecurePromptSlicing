import sys

def convert_to_int(value):
    return int(value)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Not enough arguments provided.")
        sys.exit(1)
    
    try:
        index = convert_to_int(sys.argv[1])
        target_index = convert_to_int(sys.argv[index + 1])
        print(sys.argv[target_index])
    except (IndexError, ValueError):
        print("Invalid input or index out of range.")
        sys.exit(1)