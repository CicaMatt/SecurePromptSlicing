import sys

def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        raise IndexError("Index out of range")
    return array[index]

id_sequence = [1, 2, 3, 4, 5]

def main():
    try:
        index = int(input())
        value = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(value)
    except ValueError:
        print("Invalid input", file=sys.stderr)
        sys.exit(1)
    except IndexError as e:
        print(e, file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()