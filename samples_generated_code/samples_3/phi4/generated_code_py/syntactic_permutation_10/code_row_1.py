import sys

def get_value_at_index(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

def main():
    try:
        n = int(input().strip())
        id_sequence = [1, 2, 3, 4, 5]  # Example array
        result = get_value_at_index(id_sequence, len(id_sequence), n)
        sys.exit(result)

    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()