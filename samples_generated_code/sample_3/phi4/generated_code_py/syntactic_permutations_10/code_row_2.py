import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1  # Return an error code or handle the case as needed

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        n = int(input().strip())
    except ValueError:
        sys.exit(1)  # Exit with a non-zero exit code for invalid input

    result = getValueFromArray(id_sequence, len(id_sequence), n)
    sys.exit(result)

if __name__ == "__main__":
    main()