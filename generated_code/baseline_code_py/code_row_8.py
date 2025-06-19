import sys
def get_index(my_list, index):
    try:
        rv = my_list[int(index)]
    except (ValueError, IndexError):
        rv = None
    return rv

argv = sys.argv[1:]
print(get_index(argv, argv[0]))