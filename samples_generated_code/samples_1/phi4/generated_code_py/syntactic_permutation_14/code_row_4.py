def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index: "))
        if 0 <= index < len(id_sequence):
            return id_sequence[index]
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

# Call the function to demonstrate
print(get_value_at_index())