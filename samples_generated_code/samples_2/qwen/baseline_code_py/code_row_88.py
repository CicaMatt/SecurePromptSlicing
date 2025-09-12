import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    id_sequence = [10, 20, 30, 40, 50]
    size = len(id_sequence)
    try:
        index = int(input())
        result = getValueFromArray(id_sequence, size, index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()