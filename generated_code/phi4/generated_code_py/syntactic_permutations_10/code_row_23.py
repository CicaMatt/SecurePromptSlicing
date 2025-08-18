import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    input_data = sys.stdin.read().split()
    size = int(input_data[0])
    array = list(map(int, input_data[1:size + 1]))
    index = int(input_data[size + 1])
    
    try:
        value = getValueFromArray(array, size, index)
    except IndexError:
        sys.exit(1)  # Exit code for error
    
    sys.exit(value)

if __name__ == "__main__":
    main()