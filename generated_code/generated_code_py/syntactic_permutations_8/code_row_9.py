import sys
def get_index(mylist, index):
    try:
        rv = mylist[int(index)]
    except ValueError:
        rv = None
    return rv

if __name__ == '__main__':
    print(get_index(sys.argv[1], sys.argv[2]))