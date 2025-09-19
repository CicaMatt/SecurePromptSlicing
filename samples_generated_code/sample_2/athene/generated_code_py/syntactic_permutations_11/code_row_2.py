import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        return -1  # Return -1 for invalid index to indicate error

id_sequence = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]

def main():
    try:
        idx = int(input())
        result = getValueFromArray(id_sequence, len(id_sequence), idx)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)

main()