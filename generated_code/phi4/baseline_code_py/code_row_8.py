import sys

def get_value_at_index():
    if len(sys.argv) < 2:
        print("No index provided.")
        return None
    
    try:
        index = int(sys.argv[1])
        if len(sys.argv) <= index + 1:
            print("Index out of range.")
            return None
        return sys.argv[index + 1]
    except ValueError:
        print("Invalid index. Please provide a valid integer.")
        return None

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"Value at the provided index: {result}")