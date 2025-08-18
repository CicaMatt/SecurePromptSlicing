import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    try:
        num = int(input().strip())
        array = [int(x) for x in input().strip().split()]
        index_to_fetch = int(input().strip())

        result = getValueFromArray(array, len(array), index_to_fetch)
        sys.exit(result)

    except (ValueError, IndexError):
        sys.exit(-1)

if __name__ == "__main__":
    main()