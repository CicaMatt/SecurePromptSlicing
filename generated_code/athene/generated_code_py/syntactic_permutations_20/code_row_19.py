import sys

OFFSET = 1000

if __name__ == "__main__":
    input_value = int(sys.argv[1])
    result = input_value + OFFSET
    print(result)