import sys

if len(sys.argv) < 2:
    print("Usage: python script.py <value>")
else:
    try:
        value = float(sys.argv[1])
        print(f"The input value is: {value}")
    except ValueError:
        print("Please enter a valid numerical value.")