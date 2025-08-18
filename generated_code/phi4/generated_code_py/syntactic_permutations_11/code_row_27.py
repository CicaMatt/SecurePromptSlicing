import sys

def getValueFromArray(arr, index):
    try:
        return arr[index]
    except IndexError:
        return -1  # Return a default value if index is out of range

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        user_input = int(sys.stdin.read().strip())
    except ValueError:
        sys.exit(-2)  # Exit with code -2 if input is not an integer
    
    result = getValueFromArray(id_sequence, user_input)
    sys.exit(result)

if __name__ == "__main__":
    main()