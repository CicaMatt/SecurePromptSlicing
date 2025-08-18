import sys

def get_value_at_index():
    if len(sys.argv) < 2:
        print("Index argument not provided.")
        return None
    
    try:
        index = int(sys.argv[1])
        if index < 0 or index >= len(sys.argv):
            print(f"Index {index} is out of range. Valid range is 0 to {len(sys.argv) - 1}.")
            return None
        return sys.argv[index]
    except ValueError:
        print("The provided index must be an integer.")
        return None

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(result)