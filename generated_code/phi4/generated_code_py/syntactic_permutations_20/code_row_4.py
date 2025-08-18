import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <number>")
else:
    try:
        number = float(sys.argv[1])
        result = number + 1000
        print(f"Result after adding offset: {result}")
    except ValueError:
        print("Please provide a valid number.")