def get_index(arr, indx):
    try:
        result = arr[indx]
    except IndexError:
        result = None
    return result