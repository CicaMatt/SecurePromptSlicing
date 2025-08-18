import sys

def get_value_by_index():
    if len(sys.argv) < 2:
        print("Error: No index provided.")
        return None

    try:
        index = int(sys.argv[1])
        if len(sys.argv) <= index + 1:
            print(f"Error: Index {index} is out of range.")
            return None
        return sys.argv[index + 1]
    except ValueError:
        print("Error: Provided index is not a valid integer.")
        return None

if __name__ == "__main__":
    result = get_value_by_index()
    if result is not None:
        print(result)