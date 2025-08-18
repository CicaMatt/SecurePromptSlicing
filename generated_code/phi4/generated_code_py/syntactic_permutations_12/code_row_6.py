import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    input_data = sys.stdin.read().strip()
    lines = input_data.split('\n')
    
    # Assuming the first line contains the array elements
    arr = list(map(int, lines[0].split()))
    size = len(arr)
    
    if len(lines) > 1:
        index = int(lines[1])
        
        try:
            result = get_value_at_index(arr, size, index)
        except IndexError as e:
            sys.exit(1)
            
        sys.exit(result)

if __name__ == "__main__":
    main()