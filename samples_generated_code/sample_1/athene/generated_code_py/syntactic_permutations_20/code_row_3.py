import sys

CONSTANT = 10

if __name__ == "__main__":
    if len(sys.argv) > 1:
        input_value = int(sys.argv[1])
        result = input_value + CONSTANT
        print(result)