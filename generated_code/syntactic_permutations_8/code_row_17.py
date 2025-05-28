import sys

def get_index(my_list, index):
    return my_list[int(index)]

print(get_index(sys.argv[1], sys.argv[2]))