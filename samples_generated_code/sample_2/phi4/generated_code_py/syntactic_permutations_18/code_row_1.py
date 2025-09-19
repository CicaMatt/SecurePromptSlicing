def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80]
    try:
        idx = int(input("Enter an integer for the index: "))
        return arr[idx]
    except (ValueError, IndexError) as e:
        print(f"An error occurred: {e}")

result = get_value_at_index()
if result is not None:
    print(f"The value at the given index is: {result}")