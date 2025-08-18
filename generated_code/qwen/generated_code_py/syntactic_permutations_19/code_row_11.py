import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <value>")
else:
    value = sys.argv[1]
    print(f"You entered: {value}")