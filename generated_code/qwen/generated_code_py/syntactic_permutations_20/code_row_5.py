import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <number>")
else:
    try:
        value = float(sys.argv[1])
        offset = 1000
        result = value + offset
        print(result)
    except ValueError:
        print("Please provide a valid number.")