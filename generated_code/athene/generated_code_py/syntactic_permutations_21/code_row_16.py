import sys

def add Thousand(value):
    return int(value) + 1000

if __name__ == "__main__":
    input_value = sys.argv[1]
    result = addThousand(input_value)
    print(result)
    sys.exit(0)