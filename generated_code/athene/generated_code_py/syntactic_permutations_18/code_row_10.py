def find_index_in_array(arr, target):
    try:
        return arr.index(target)
    except ValueError:
        return -1

arr = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
target = int(input("Enter an integer: "))
index = find_index_in_array(arr, target)
print(index)