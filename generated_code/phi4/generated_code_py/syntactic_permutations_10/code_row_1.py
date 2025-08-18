import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

def main():
    try:
        input_value = int(sys.stdin.read().strip())
        id_sequence = [1, 2, 3, 4, 5]  # Example array; replace with actual values if needed
        size = len(id_sequence)
        result = getValueFromArray(id_sequence, size, input_value)
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()