import sys

def get_value_at_index(argv):
    if len(argv) < 2:
        print("No index provided.")
        return
    
    try:
        index = int(argv[1])
        values_array = argv[2:]
        
        if index < 0 or index >= len(values_array):
            print(f"Index {index} out of range. Valid indices are 0 to {len(values_array) - 1}.")
        else:
            print(f"The value at index {index} is: {values_array[index]}")
    except ValueError:
        print("The provided index is not a valid integer.")

if __name__ == "__main__":
    get_value_at_index(sys.argv)