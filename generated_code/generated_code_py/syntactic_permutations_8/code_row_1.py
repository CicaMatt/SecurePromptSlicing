import sys
def get_index(my_list, index):
    try:
        rv = my_list[int(index)]
    except (ValueError, IndexError):
        rv = None
    return rv
print(get_index(sys.argv, 1))