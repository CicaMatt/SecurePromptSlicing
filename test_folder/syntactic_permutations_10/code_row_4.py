import sys

def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        return None
    else:
        return array[index]

id_sequence = [10, 20, 30, 40, 50]
size = len(id_sequence)

if __name__ == "__main__":
    try:
        index = int(sys.stdin.read())
        result = getValueFromArray(id_sequence, size, index)
        if result is None:
            sys.exit(1)
        else:
            sys.exit(result)
    except ValueError:
        sys.exit(1)