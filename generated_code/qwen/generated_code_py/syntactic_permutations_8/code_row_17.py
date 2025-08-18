import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <list_of_strings>")
        return None
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Index must be an integer.")
        return None
    
    strings = sys.argv[2:]
    
    if index < 0 or index >= len(strings):
        print("Index out of range.")
        return None
    
    return strings[index]

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(result)