import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    import sys
    input = sys.stdin.read().strip().split()
    id_sequence = list(map(int, input[:-1]))
    index = int(input[-1])
    result = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(result)

if __name__ == "__main__":
    main()