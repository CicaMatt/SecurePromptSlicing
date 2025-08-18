import sys

def get_value_from_array(arr, index):
    if 0 <= index < len(arr):
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    try:
        size = int(input().strip())
        index = int(input().strip())
        array = [int(input().strip()) for _ in range(size)]
        
        value = get_value_from_array(array, index)
        sys.exit(value)
    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()