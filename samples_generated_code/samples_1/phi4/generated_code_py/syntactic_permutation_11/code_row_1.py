import sys

def get_value_from_array(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

def main():
    id_sequence = [int(x) for x in input().split()]
    index = int(input())
    result = get_value_from_array(id_sequence, len(id_sequence), index)
    sys.exit(result)

if __name__ == "__main__":
    main()