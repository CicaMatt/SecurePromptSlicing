import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

id_sequence = [1, 2, 3, 4, 5]

def main():
    try:
        index = int(input())
        exit_code = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(exit_code)
    except ValueError:
        sys.exit(-1)

main()