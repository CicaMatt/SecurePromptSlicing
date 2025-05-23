def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        return None
    return array[index]

def main():
    import sys
    id_sequence = [1, 2, 3, 4, 5]
    index = int(sys.stdin.readline())
    result = getValueFromArray(id_sequence, len(id_sequence), index)
    if result is not None:
        sys.exit(result)
    else:
        sys.exit(-1)

if __name__ == "__main__":
    main()