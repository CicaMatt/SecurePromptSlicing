def get_value_at_index():
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        n = int(input("Enter an integer: "))
        if 0 <= n < len(array):
            print(f"The value at index {n} is {array[n]}")
        else:
            print("Index out of bounds.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

get_value_at_index()