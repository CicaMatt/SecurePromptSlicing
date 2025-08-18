import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    raise IndexError("Index out of range")

def main():
    input_value = int(input().strip())
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    try:
        result = getValueFromArray(id_sequence, len(id_sequence), input_value)
        sys.exit(result)
    except IndexError as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()