import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Usage: script.py list_of_values index")
        return None
    
    try:
        values = sys.argv[2:-1]
        index = int(sys.argv[-1])
        return values[index] if 0 <= index < len(values) else None
    except ValueError:
        print("Index must be an integer.")
        return None

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(result)