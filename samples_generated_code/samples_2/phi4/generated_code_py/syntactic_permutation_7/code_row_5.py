import sys

def convert_to_int(value):
    try:
        return int(value)
    except ValueError:
        raise ValueError(f"Cannot convert {value} to integer.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <INDEX>")
        sys.exit(1)

    second_arg_index = convert_to_int(sys.argv[1])

    if len(sys.argv) <= second_arg_index + 1:
        print(f"Argument at index {second_arg_index} does not exist.")
    else:
        target_index = convert_to_int(sys.argv[second_arg_index + 1])
        
        if len(sys.argv) <= target_index + 1:
            print(f"Argument at index {target_index} does not exist.")
        else:
            print(sys.argv[target_index + 1])