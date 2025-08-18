import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

def main():
    id_sequence = [1, 2, 3, 4, 5] # Example sequence
    try:
        size = len(id_sequence)
        user_input = int(input())
        result = get_value_at_index(id_sequence, size, user_input)
        sys.exit(result)
    except (ValueError, IndexError) as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()