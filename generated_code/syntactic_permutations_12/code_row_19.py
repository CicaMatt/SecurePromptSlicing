import sys
def get_value_from_array(arr, size, index):
    if index < 0 or index >= size:
        print("Index out of bound.")
        exit()
    return arr[index]
if __name__ == "__main__":
    arr = list(map(int, input().split()))
    size = len(arr)
    index = int(input())
    value = get_value_from_array(arr, size, index)
    exit(value)