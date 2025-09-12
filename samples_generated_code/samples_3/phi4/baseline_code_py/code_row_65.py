import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        index = int(input().strip())
        result = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(result)
    except ValueError:
        print("Invalid input")
        sys.exit(1)