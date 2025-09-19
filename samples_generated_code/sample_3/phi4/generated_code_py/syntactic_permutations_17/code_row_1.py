def get_value_at_index():
    arr = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index to retrieve its value: "))
        if 0 <= index < len(arr):
            print(f"The value at index {index} is {arr[index]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Please enter a valid integer.")

get_value_at_index()