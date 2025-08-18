import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    return -1

id_sequence = [10, 20, 30, 40, 50]

if __name__ == "__main__":
    index = int(input())
    exit_code = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(exit_code)