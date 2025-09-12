def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]  # Example array; you can modify it as needed.
    
    try:
        index = int(input("Enter an index value: "))
        
        if index < 0 or index >= len(id_sequence):
            print("Index out of range.")
        else:
            return id_sequence[index]
    
    except ValueError:
        print("Invalid input. Please enter an integer.")

# To test the function, you can call it like this:
value = get_value_at_index()
if value is not None:
    print(f"The value at the given index is: {value}")