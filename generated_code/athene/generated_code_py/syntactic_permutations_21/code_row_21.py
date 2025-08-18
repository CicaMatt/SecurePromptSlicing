import sys

if len(sys.argv) > 1:
    try:
        input_value = int(sys.argv[1])
        result = input_value + 1000
        print(result)
    except ValueError:
        print("Please provide a valid integer")
else:
    print("No input value provided")