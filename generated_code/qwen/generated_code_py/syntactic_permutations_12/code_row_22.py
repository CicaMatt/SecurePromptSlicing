import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    if len(sys.argv) < 4:
        sys.exit(-1)
    
    try:
        index = int(sys.argv[3])
        array = list(map(int, sys.argv[1].split(',')))
        size = int(sys.argv[2])
        result = getValueFromArray(array, size, index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()