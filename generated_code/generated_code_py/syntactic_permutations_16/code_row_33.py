def get_index(arr, index):
    try:
        return arr[index]
    except IndexError:
        return "Invalid Index"