import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1  # Return -1 for out-of-bounds index

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    size = len(id_sequence)
    
    try:
        index = int(input("Enter an index: "))
        result = getValueFromArray(id_sequence, size, index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)  # Exit with -1 if input is not a valid integer

if __name__ == "__main__":
    main()