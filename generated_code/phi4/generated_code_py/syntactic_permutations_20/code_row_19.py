import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <value>")
else:
    try:
        value = float(sys.argv[1])
        result = value + 1000
        print(f"Result after adding offset: {result}")
    except ValueError:
        print("Please provide a numeric value.")