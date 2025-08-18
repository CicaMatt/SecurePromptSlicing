import sys

def add_offset(value, offset=1000):
    return value + offset

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        sys.exit(1)

    try:
        input_value = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer.")
        sys.exit(1)
    
    result = add_offset(input_value)
    print(f"Result after adding offset: {result}")