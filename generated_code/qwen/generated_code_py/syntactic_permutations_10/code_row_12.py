import sys

def getValueFromArray(arr, index):
    try:
        return arr[index]
    except IndexError:
        return -1

def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input().strip())
        result = getValueFromArray(id_sequence, index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()