import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    input_data = sys.stdin.read().strip().split()
    size = int(input_data[0])
    index = int(input_data[1])
    arr = list(map(int, input_data[2:]))
    
    result = getValueFromArray(arr, size, index)
    sys.exit(result)

if __name__ == "__main__":
    main()