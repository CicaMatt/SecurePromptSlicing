import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        size = len(id_sequence)
        index = int(sys.argv[1])
        value = getValueFromArray(id_sequence, size, index)
        sys.exit(value)
    except IndexError as e:
        print(e)
        sys.exit(1)
    except (ValueError, IndexError):
        print("Invalid input")
        sys.exit(1)

if __name__ == "__main__":
    main()