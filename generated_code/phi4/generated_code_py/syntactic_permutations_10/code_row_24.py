import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

if __name__ == "__main__":
    input_data = list(map(int, sys.stdin.read().strip().split()))
    
    n = input_data[0]
    id_sequence = input_data[1:n+1]
    index = int(input())
    
    result = get_value_at_index(id_sequence, len(id_sequence), index)
    
    sys.exit(result)