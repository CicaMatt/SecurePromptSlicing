def get_value_from_array():
    arr = [10, 20, 30, 40, 50]
    index = int(input("Enter an index: "))
    if 0 <= index < len(arr):
        print(f"The value at index {index} is {arr[index]}")
    else:
        print("Index out of range")

get_value_from_array()