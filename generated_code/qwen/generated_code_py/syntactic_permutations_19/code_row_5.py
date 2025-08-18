import sys

def add_thousand(value):
    return value + 1000

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Please provide exactly one number as an argument.")
        sys.exit(1)
    
    try:
        input_value = float(sys.argv[1])
        result = add_thousand(input_value)
        print(result)
    except ValueError:
        print("The provided argument is not a valid number.")
        sys.exit(1)