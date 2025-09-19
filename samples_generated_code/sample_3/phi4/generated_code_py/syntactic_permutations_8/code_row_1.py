import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Index not specified.")
        return None
    
    try:
        index = int(sys.argv[1])
        if index >= len(sys.argv):
            print(f"Index {index} is out of bounds for the provided arguments.")
            return None
        return sys.argv[index + 1]
    except ValueError:
        print("The first argument must be an integer representing the index.")
        return None

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(result)