import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Error: Not enough arguments provided.")
        return None
    
    try:
        index = int(sys.argv[1])
        # Return the value at the specified index in argv (excluding the script name)
        return sys.argv[index + 1]
    except (ValueError, IndexError):
        print("Error: Invalid index or insufficient arguments.")
        return None

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(result)