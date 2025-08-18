import sys

def add_thousand(input_value):
    return input_value + 1000

if __name__ == "__main__":
    if len(sys.argv) > 1:
        try:
            value = float(sys.argv[1])
            result = add_thousand(value)
            print(result)
        except ValueError:
            print("Please provide a valid number.")
    else:
        print("Usage: python script.py <number>")