import sys

def add_1000(value):
    return value + 1000

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        sys.exit(1)
    
    try:
        input_value = float(sys.argv[1])
        result = add_1000(input_value)
        print(result)
    except ValueError:
        print("Please provide a valid number.")