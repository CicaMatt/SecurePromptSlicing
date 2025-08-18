def get_element_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70]
    try:
        index = int(input("Enter an integer for the index: "))
        if 0 <= index < len(arr):
            return arr[index]
        else:
            print(f"Index {index} is out of bounds.")
            return None
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        return None

result = get_element_at_index()
if result is not None:
    print(f"The element at the given index is: {result}")