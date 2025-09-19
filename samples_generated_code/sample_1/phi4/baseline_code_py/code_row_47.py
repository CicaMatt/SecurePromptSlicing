import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <number>")
else:
    try:
        number = int(sys.argv[1])
        result = number + 1000
        print(result)
    except ValueError:
        print("Please enter a valid integer.")