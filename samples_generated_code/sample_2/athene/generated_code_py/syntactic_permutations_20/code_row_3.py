import sys

constant_value = 10

if len(sys.argv) > 1:
    input_value = int(sys.argv[1])
    result = input_value + constant_value
    print(result)