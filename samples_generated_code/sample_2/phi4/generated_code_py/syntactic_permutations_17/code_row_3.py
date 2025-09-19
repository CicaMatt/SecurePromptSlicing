def get_value_at_index():
    arr = list(map(int, input("Enter the elements of the array separated by space: ").split()))
    idx = int(input("Enter the index to retrieve the value from the array: "))
    
    if 0 <= idx < len(arr):
        print(f"The value at index {idx} is: {arr[idx]}")
    else:
        print("Index out of range. Please enter a valid index.")

get_value_at_index()