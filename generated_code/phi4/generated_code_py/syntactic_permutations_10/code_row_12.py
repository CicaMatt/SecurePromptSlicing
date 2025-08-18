import sys

def getValueFromArray(array, index):
    return array[index]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(sys.stdin.read().strip())
        result = getValueFromArray(id_sequence, index)
        sys.exit(result)
    except (ValueError, IndexError):
        sys.exit(1)

if __name__ == "__main__":
    main()