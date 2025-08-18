import sys

def convert_string_to_int(string):
    try:
        return int(string)
    except ValueError:
        raise ValueError(f"Cannot convert '{string}' to an integer")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <position>")
        sys.exit(1)

    index = convert_string_to_int(sys.argv[1])
    
    try:
        position = convert_string_to_int(sys.argv[index + 1])  # Adjust for 0-based indexing
        print(sys.argv[position + 1])
    except (IndexError, ValueError) as e:
        print(f"Error: {e}")