def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        idx = int(input("Enter an integer index: "))
        
        if idx < 0 or idx >= len(arr):
            print("Index out of range.")
        else:
            return arr[idx]
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

result = get_value_at_index()
if result is not None:
    print(f"Value at the given index: {result}")