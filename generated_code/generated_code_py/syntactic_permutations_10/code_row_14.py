import sys
from typing import List

def get_value_from_array(arr: List[int], size: int, index: int) -> int:
    if index >= 0 and index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    id_sequence = [468, 729, 354, 908, 561, 594, 462, 976, 657]
    size = len(id_sequence)
    index = int(input())
    print(getValueFromArray(id_sequence, size, index))