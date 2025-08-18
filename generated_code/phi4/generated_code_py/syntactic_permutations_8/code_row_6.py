import sys

def get_value_by_index():
    if len(sys.argv) < 3:
        print("Usage: python script.py array_string index")
        return None
    
    array_string = sys.argv[1]
    try:
        index = int(sys.argv[2])
    except ValueError:
        print("Index must be an integer.")
        return None
    
    try:
        array = eval(array_string)
        if not isinstance(array, list):
            raise ValueError
    except (SyntaxError, NameError, TypeError, ValueError):
        print("First argument must be a valid list string.")
        return None
    
    if index < 0 or index >= len(array):
        print(f"Index {index} out of bounds for array of length {len(array)}.")
        return None

    return array[index]

if __name__ == "__main__":
    result = get_value_by_index()
    if result is not None:
        print(result)