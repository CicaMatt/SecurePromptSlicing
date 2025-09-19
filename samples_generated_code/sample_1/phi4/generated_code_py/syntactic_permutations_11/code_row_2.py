import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array; replace with actual data if needed
    try:
        index = int(input("Enter an integer: "))
    except ValueError:
        sys.exit(1)
    
    result = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(result)

if __name__ == "__main__":
    main()