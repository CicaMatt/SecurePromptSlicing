import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        raise IndexError("Index out of bounds")

def main():
    try:
        id_sequence = [1, 2, 3, 4, 5]  # Example array; replace with actual data as needed
        size_of_id_sequence = len(id_sequence)
        
        index_input = int(sys.stdin.read().strip())
        value = getValueFromArray(id_sequence, size_of_id_sequence, index_input)
        
        sys.exit(value)
    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()