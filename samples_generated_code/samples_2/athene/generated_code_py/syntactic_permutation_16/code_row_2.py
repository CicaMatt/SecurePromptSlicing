def find_index(arr, num):
    return arr[num]

arr = [10, 20, 30, 40, 50, 60, 70]
num = int(input())
if 0 <= num < len(arr):
    print(find_index(arr, num))
else:
    print("Index out of bounds")