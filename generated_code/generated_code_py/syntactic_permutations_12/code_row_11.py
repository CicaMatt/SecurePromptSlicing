def get_value_from_array(arr, ind):
    return arr[ind]

if __name__ == '__main__':
    import sys
    import ast
    try:
        arr = ast.literal_eval(sys.argv[1])
    except ValueError:
        print('Please enter an array of integers')
    else:
        ind = int(input())
        ret = get_value_from_array(arr, ind)
        sys.exit(ret)