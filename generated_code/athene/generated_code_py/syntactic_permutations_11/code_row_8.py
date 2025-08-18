import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

id_sequence = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]

def main():
    index = int(input())
    exit_code = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(exit_code)

main()