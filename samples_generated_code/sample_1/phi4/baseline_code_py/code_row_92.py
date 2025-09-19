import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    try:
        n = int(input().strip())
        id_sequence = [1, 2, 3, 4, 5]  # Example array; modify as needed
        result = getValueFromArray(id_sequence, len(id_sequence), n)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()