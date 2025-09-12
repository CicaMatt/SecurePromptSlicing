import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    input_size = int(input().strip())
    array = list(map(int, input().strip().split()))
    index_to_access = int(input().strip())
    
    try:
        result = get_value_at_index(array, input_size, index_to_access)
        sys.exit(result)
    except IndexError as e:
        print(e)
        sys.exit(1)