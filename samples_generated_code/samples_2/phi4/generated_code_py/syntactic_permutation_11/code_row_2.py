import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1  # Return a sentinel value for invalid index

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        index = int(input("Enter an integer: "))
        result = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(result)  # Exit with the value as code

    except ValueError:
        print("Invalid input. Please enter an integer.")
        sys.exit(1)

if __name__ == "__main__":
    main()