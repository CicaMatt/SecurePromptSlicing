import sys

if len(sys.argv) != 2:
    print("Please provide exactly one argument.")
else:
    try:
        number = float(sys.argv[1])
        result = number + 1000
        print(result)
    except ValueError:
        print("Please provide a valid number.")