import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    size = len(id_sequence)
    
    try:
        index = int(input().strip())
        result = getValueFromArray(id_sequence, size, index)
        sys.exit(result)
    except ValueError:
        print("Please enter a valid integer.", file=sys.stderr)
        sys.exit(1)
    except IndexError as e:
        print(e, file=sys.stderr)
        sys.exit(2)