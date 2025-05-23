import sys

def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        raise IndexError("Index out of bounds")
    return array[index]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(sys.stdin.readline())
        value = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(value)
    except ValueError:
        print("Invalid input")
        sys.exit(1)

if __name__ == "__main__":
    main()