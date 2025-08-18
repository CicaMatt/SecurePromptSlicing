import sys

OFFSET = 10

if len(sys.argv) > 1:
    try:
        input_value = int(sys.argv[1])
        result = input_value + OFFSET
        print(result)
    except ValueError:
        print("Please provide a valid integer as an argument.")
else:
    print("No value provided. Please provide an integer as an argument.")