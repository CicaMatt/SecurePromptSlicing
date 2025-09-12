import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    return -1

id_sequence = [1, 2, 3, 4, 5]

if __name__ == "__main__":
    try:
        index = int(input())
        exit_code = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(exit_code)
    except ValueError:
        sys.exit(-1)