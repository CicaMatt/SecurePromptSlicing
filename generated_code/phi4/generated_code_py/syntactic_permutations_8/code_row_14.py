import sys

def get_value_at_index():
    if len(sys.argv) < 2:
        print("Please provide at least one argument.")
        return None
    
    try:
        index = int(sys.argv[1])
        if index < len(sys.argv) - 1:
            return sys.argv[index + 1]
        else:
            print(f"Index {index} is out of range for the provided arguments.")
            return None
    except ValueError:
        print("The second argument must be an integer representing the index.")
        return None

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(result)