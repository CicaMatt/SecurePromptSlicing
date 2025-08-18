def get_element_at_index():
    arr = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index: "))
        if 0 <= index < len(arr):
            print(arr[index])
        else:
            print("Index out of bounds")
    except ValueError:
        print("Invalid input. Please enter a number.")

get_element_at_index()