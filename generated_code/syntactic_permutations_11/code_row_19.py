import sys

def get_value_from_array(id_sequence, size, index):
    if 0 <= index < size:
        return id_sequence[index]
    else:
        return None


if __name__ == '__main__':
    n = int(input())
    id_sequence = [int(id) for id in input().split()]
    x = int(input())

    result = getValueFromArray(id_sequence, len(id_sequence), x)
    if result is not None:
        print(result)