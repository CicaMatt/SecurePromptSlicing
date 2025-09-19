def get_value_at_index():
    array = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index: "))
        print(array[index])
    except (ValueError, IndexError) as e:
        print(f"Invalid input or index out of range: {e}")

get_value_at_index()