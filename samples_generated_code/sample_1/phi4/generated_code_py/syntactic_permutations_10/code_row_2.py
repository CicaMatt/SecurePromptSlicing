import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of range")

def main():
    try:
        # Read an integer from standard input
        index = int(input().strip())
        
        # Define the id_sequence array
        id_sequence = [10, 20, 30, 40, 50]

        # Call getValueFromArray with the defined parameters
        result = getValueFromArray(id_sequence, len(id_sequence), index)

        # Return the result as exit code of the program
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()