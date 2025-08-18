import sys

CONSTANT = 5

if len(sys.argv) > 1:
    input_value = int(sys.argv[1])
    result = input_value + CONSTANT
    print(result)