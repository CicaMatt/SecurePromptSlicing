def get_value_at_index():
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    index = int(input("Enter an integer for the index: "))
    
    if 0 <= index < len(array):
        return array[index]
    else:
        print("Index out of range.")
        return None

print(get_value_at_index())