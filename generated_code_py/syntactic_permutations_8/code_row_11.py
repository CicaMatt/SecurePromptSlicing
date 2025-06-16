import sys
def get_index(my_list, index):
    try:
        return my_list[int(index)]
    except IndexError as e:
        print("Invalid index")
        raise e