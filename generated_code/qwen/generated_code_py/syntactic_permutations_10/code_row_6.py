import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    id_sequence = [10, 20, 30, 40, 50]
    size = len(id_sequence)
    try:
        index = int(input().strip())
        result = get_value_at_index(id_sequence, size, index)
    except ValueError:
        result = -1
    sys.exit(result)

if __name__ == "__main__":
    main()