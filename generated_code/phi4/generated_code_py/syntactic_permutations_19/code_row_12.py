import sys

def add_to_value(input_value):
    number = float(input_value)
    result = number + 10
    return result

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
    else:
        input_value = sys.argv[1]
        try:
            output = add_to_value(input_value)
            print(f"Result: {output}")
        except ValueError:
            print("Please provide a valid number.")