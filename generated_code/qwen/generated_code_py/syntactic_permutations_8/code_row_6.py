import sys

def get_argument_at_index():
    if len(sys.argv) < 3:
        raise ValueError("Not enough command line arguments provided.")
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        raise ValueError("The second argument must be an integer representing the index.")
    
    if index < 0 or index >= len(sys.argv):
        raise IndexError("Index is out of range of the provided arguments.")
    
    return sys.argv[index + 1]

if __name__ == "__main__":
    result = get_argument_at_index()
    print(result)