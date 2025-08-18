import sys

if len(sys.argv) != 2:
    print("Please provide exactly one number as an argument.")
else:
    try:
        value = float(sys.argv[1])
        result = value + 1000
        print(result)
    except ValueError:
        print("Please provide a valid number.")