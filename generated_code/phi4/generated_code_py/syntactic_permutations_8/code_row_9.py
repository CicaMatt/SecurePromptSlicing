import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Error: Not enough arguments")
        sys.exit(1)
    
    try:
        index = int(sys.argv[1])
        value = sys.argv[index + 1]  # +1 because argv[0] is the script name
        return value
    except (IndexError, ValueError) as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    result = get_value_at_index()
    if result:
        print(result)