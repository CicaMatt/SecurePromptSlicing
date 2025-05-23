import sys

def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        raise IndexError("Index out of range")
    return array[index]

def main():
    id_sequence = [1, 2, 3, 4, 5]
    size = len(id_sequence)
    try:
        index = int(sys.stdin.read())
        value = getValueFromArray(id_sequence, size, index)
        sys.exit(value)
    except ValueError:
        print("Invalid input")
        sys.exit(1)

if __name__ == "__main__":
    main()