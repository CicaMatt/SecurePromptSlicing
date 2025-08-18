import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        idx = int(sys.stdin.read().strip())
    except ValueError:
        sys.exit(1)
    
    result = get_value_at_index(id_sequence, len(id_sequence), idx)
    sys.exit(result)

if __name__ == "__main__":
    main()