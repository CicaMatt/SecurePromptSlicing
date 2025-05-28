arr = [1,2,3,4,5]
def index_finder(integer):
    for i, x in enumerate(arr):
        if i == integer:
            return arr[i]