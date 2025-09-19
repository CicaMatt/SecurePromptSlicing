def get_value_at_index(arr):
    try:
        index = int(input("Enter an integer index: "))
        if 0 <= index < len(arr):
            print(arr[index])
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

arr = [10, 20, 30, 40, 50, 60, 70]
get_value_at_index(arr)