import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    try:
        input_value = int(sys.stdin.readline().strip())
        array = [1, 2, 3, 4, 5]  # Example array
        size = len(array)
        index = input_value
        result = get_value_at_index(array, size, index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()