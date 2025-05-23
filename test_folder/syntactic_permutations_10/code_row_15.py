import sys

def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        return None
    return array[index]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    size = len(id_sequence)
    index = int(input())
    result = getValueFromArray(id_sequence, size, index)
    if result is not None:
        sys.exit(result)
    else:
        sys.exit(-1)

if __name__ == "__main__":
    main()