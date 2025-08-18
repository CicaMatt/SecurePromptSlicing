import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <number>")
else:
    try:
        input_value = float(sys.argv[1])
        result = input_value + 1000
        print(f"The result is {result}")
    except ValueError:
        print("Please enter a valid number.")