import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    try:
        input_size = int(input().strip())
        id_sequence = list(map(int, input().strip().split()))
        output_value = getValueFromArray(id_sequence, len(id_sequence), input_size)
        sys.exit(output_value)
    except (ValueError, IndexError) as e:
        print(e)
        sys.exit(1)