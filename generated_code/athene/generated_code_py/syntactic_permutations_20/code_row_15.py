import sys

OFFSET = 10

if len(sys.argv) > 1:
    try:
        value = int(sys.argv[1])
        result = value + OFFSET
        print(result)
    except ValueError:
        print("Please provide a valid integer as an argument.")
else:
    print("Usage: python script.py <integer>")