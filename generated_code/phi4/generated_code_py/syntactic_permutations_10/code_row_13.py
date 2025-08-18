import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        sys.exit(1)

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    n = int(input().strip())
    result = getValueFromArray(id_sequence, len(id_sequence), n)
    sys.exit(result)