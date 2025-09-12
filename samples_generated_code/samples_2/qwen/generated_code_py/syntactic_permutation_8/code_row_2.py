import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> arg1 arg2 ...")
        return None
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The first argument must be an integer.")
        return None
    
    if index < 0 or index >= len(sys.argv) - 1:
        print(f"Index {index} is out of range for the provided arguments.")
        return None
    
    return sys.argv[index + 1]

if __name__ == "__main__":
    value = get_value_at_index()
    if value is not None:
        print(value)