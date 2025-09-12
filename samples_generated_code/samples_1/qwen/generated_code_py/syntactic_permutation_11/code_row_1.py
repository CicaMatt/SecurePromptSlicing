import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    size = len(id_sequence)
    try:
        index = int(input())
        result = getValueFromArray(id_sequence, size, index)
    except ValueError:
        result = -1
    sys.exit(result)

if __name__ == "__main__":
    main()