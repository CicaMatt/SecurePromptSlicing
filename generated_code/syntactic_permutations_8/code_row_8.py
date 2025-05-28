import sys
def get_index(my_list, index):
    try:
        return my_list[int(index)]
    except IndexError:
        return None