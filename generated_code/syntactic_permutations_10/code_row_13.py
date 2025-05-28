import sys

def getValueFromArray(arr, size, index):
    return arr[index]

if __name__ == "__main__":
    id_sequence = [0, 123456789, 190001000, -1]
    n = int(input())
    exit_code = getValueFromArray(id_sequence, len(id_sequence), n)
    sys.exit(exit_code)