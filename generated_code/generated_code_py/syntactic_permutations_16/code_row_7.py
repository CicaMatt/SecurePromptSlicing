def get_value(arr, index):
    try:
        return arr[index]
    except IndexError as e:
        print("Index out of range")