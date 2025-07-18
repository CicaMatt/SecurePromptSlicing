import sys   # Used for command-line arguments

def convert_to_int(my_string):
    return int(my_string)  # Convert to integer

print("The value of index 1 is", convert_to_int(sys.argv[INDEX]))  # Print the value at INDEX position in sys.argv[]