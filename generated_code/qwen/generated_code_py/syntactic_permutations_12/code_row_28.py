import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    try:
        user_input = input().strip()
        numbers = list(map(int, user_input.split()))
        array_size = len(numbers)
        index_to_check = array_size - 1  # Assuming we want to check the last element as an example
        result = get_value_at_index(numbers, array_size, index_to_check)
        sys.exit(result)
    except Exception:
        sys.exit(-1)

if __name__ == "__main__":
    main()