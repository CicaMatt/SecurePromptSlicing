import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return None

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        input_value = int(input().strip())
    except ValueError:
        sys.exit(1)
    
    result = getValueFromArray(id_sequence, len(id_sequence), input_value)
    if result is not None:
        sys.exit(result)
    else:
        sys.exit(1)

if __name__ == "__main__":
    main()