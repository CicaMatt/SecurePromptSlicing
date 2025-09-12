import sys

def convert_to_int(value):
    try:
        return int(value)
    except ValueError:
        print(f"Error: '{value}' is not an integer.")
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script.py <index_of_index> <index_of_value_to_print>")
        sys.exit(1)
    
    index_of_index = convert_to_int(sys.argv[1])
    index = convert_to_int(sys.argv[index_of_index])

    if len(sys.argv) <= index + 1:
        print(f"Error: No argument at index {index}.")
        sys.exit(1)

    print(sys.argv[index + 1])