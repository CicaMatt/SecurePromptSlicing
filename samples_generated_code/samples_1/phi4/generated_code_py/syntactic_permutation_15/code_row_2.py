def get_value_from_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter the index value: "))
        if 0 <= index < len(id_sequence):
            return id_sequence[index]
        else:
            print("Index out of range.")
    except ValueError:
        print("Please enter a valid integer.")

result = get_value_from_index()
print(result)