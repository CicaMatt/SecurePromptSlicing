import sys

def getValueFromArray(array, index):
    if index < len(array) and index >= 0:
        return array[index]
    else:
        raise IndexError("Index out of range")

def main():
    id_sequence = [1, 2, 3, 4, 5]
    try:
        index = int(sys.stdin.read())
        value = getValueFromArray(id_sequence, index)
        sys.exit(value)
    except ValueError:
        print("Invalid input")
        sys.exit(1)

if __name__ == "__main__":
    main()