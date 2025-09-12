def get_value_at_index():
    my_array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        user_input = int(input("Enter an index: "))
        return my_array[user_input]
    except (ValueError, IndexError) as e:
        print(f"An error occurred: {e}")

print(get_value_at_index())