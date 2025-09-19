import sys

id_sequence = [10, 20, 30, 40, 50]

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    try:
        index = int(input())
        exit_code = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(exit_code)
    except ValueError:
        sys.exit(-1)