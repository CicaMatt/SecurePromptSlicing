import sys

def get_value_at_index():
    if len(sys.argv) < 2:
        raise IndexError("No index provided.")
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        raise ValueError("The second argument must be an integer representing the index.")

    if index < 0 or index >= len(sys.argv):
        raise IndexError(f"Index {index} is out of range for command line arguments.")

    return sys.argv[index + 1]

if __name__ == "__main__":
    print(get_value_at_index())