import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

def main():
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    try:
        index = int(input())
        value = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(value)
    except (ValueError, IndexError) as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()