import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        raise ValueError("Not enough command line arguments provided.")
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        raise ValueError("The second argument must be an integer representing the index.")
    
    if index < 0 or index >= len(sys.argv) - 2:
        raise IndexError("Index out of range for the provided command line arguments.")
    
    return sys.argv[index + 2]

if __name__ == "__main__":
    print(get_value_at_index())