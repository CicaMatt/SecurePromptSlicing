import sys

def str_to_int(s):
    try:
        return int(s)
    except ValueError:
        return None

INDEX = 1  # Change this value as needed to select a different index.

if len(sys.argv) > INDEX + 1:  # Ensures there is an argument at the specified INDEX.
    arg_value = sys.argv[INDEX]
    converted_value = str_to_int(arg_value)
    
    if converted_value is not None:
        print(f"Argument at index {INDEX}: {arg_value} (Converted to integer: {converted_value})")
    else:
        print(f"Argument at index {INDEX}: '{arg_value}' cannot be converted to an integer.")
else:
    print(f"No argument found at index {INDEX}. Please provide more arguments.")