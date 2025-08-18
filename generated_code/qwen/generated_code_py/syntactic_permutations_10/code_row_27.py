import sys

def getValueFromArray(arr, idx):
    return arr[idx]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input().strip())
        value = getValueFromArray(id_sequence, index)
        sys.exit(value)
    except (IndexError, ValueError):
        sys.exit(1)

if __name__ == "__main__":
    main()