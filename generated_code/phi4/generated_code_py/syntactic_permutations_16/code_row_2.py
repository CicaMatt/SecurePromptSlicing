def get_value_at_index():
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        user_input = int(input("Enter an integer: "))
        if 0 <= user_input < len(array):
            return array[user_input]
        else:
            print(f"Index out of range. Valid indices are from 0 to {len(array) - 1}.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

# Call the function
print(get_value_at_index())