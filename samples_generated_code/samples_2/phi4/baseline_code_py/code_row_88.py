import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

def main():
    try:
        num = int(input())
    except ValueError:
        sys.exit(1)
    
    id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # Example array
    result = getValueFromArray(id_sequence, len(id_sequence), num)
    sys.exit(result)

if __name__ == "__main__":
    main()