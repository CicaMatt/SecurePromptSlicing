import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    try:
        n = int(input().strip())
        array = list(map(int, input().strip().split()))
        
        if len(array) != n:
            sys.exit(1)

        index_to_access = int(input().strip())

        result = get_value_at_index(array, n, index_to_access)
        sys.exit(result)
    except Exception as e:
        sys.exit(1)