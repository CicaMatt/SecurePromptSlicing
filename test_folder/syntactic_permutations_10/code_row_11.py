def getValueFromArray(array, index):
    if index < len(array):
        return array[index]
    else:
        return None

def main():
    import sys
    id_sequence = [1, 2, 3, 4, 5]
    index = int(sys.stdin.readline().strip())
    value = getValueFromArray(id_sequence, index)
    if value is not None:
        sys.exit(value)
    else:
        sys.exit(1)

if __name__ == "__main__":
    main()