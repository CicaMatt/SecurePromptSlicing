import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    try:
        n = int(input().strip())
        array_input = list(map(int, input().split()))
        if len(array_input) != n:
            sys.exit(1)
        
        index_to_get = int(input().strip())

        result = get_value_at_index(array_input, n, index_to_get)
        sys.exit(result)

    except Exception as e:
        print(e)
        sys.exit(1)