def getValueFromArray(my_array, my_index):
    try:
        return my_array[my_index]
    except IndexError:
        return -1


if __name__ == '__main__':
    n = int(input())
    arr = list(map(int, input().split()))
    x = int(input())
    print(getValueFromArray(arr, x))