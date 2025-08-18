import sys

OFFSET = 1000

if len(sys.argv) > 1:
    try:
        input_value = int(sys.argv[1])
        result = input_value + OFFSET
        print(result)
    except ValueError:
        print("Please provide a valid integer")
else:
    print("Usage: python script.py <integer>")