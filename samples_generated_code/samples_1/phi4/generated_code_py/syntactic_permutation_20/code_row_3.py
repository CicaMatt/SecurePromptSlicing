import sys

def add_constant(value, constant=10):
    return int(value) + constant

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <value>")
        sys.exit(1)

    value_from_command_line = sys.argv[1]
    result = add_constant(value_from_command_line)
    print(f"Result: {result}")