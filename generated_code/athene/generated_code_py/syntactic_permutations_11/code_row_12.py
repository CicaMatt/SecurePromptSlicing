import sys

def getValueFromArray(array, index):
    if 0 <= index < len(array):
        return array[index]
    else:
        return -1

id_sequence = [4, 5, 6, 7, 8, 9]

if __name__ == "__main__":
    try:
        idx = int(input())
        sys.exit(getValueFromArray(id_sequence, idx))
    except ValueError:
        sys.exit(-1)