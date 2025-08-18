import sys

def get_value_at_index(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array; adjust as needed
    size_of_array = len(id_sequence)
    
    try:
        index = int(sys.stdin.read().strip())
    except ValueError:
        sys.exit(-1)  # Exit with code -1 if input is not an integer
    
    result = get_value_at_index(id_sequence, size_of_array, index)
    sys.exit(result)

if __name__ == "__main__":
    main()