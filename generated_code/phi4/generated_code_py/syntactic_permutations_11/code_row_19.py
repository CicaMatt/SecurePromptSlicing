import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    # Example array and parameters for demonstration purposes
    id_sequence = [10, 20, 30, 40, 50]  # Replace with actual input as needed
    
    try:
        index = int(sys.argv[1])
        value = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(value)
    except (IndexError, ValueError) as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()