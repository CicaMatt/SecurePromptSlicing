import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

def main():
    try:
        index = int(input().strip())
        id_sequence = [10, 20, 30, 40, 50]  # Example array
        result = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()