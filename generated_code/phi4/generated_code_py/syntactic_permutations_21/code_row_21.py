import sys

def add_and_print():
    try:
        # Read the first command-line argument (after script name)
        input_value = int(sys.argv[1])
        
        # Add 1000 to the input value
        result = input_value + 1000
        
        # Print the result
        print(result)
    
    except IndexError:
        print("Please provide a number as an argument.")
    except ValueError:
        print("The provided argument is not a valid integer.")

if __name__ == "__main__":
    add_and_print()