def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        n = int(input("Enter an integer: "))
        if 0 <= n < len(arr):
            return arr[n]
        else:
            print("Index out of range.")
            return None
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        return None

# Example usage
result = get_value_at_index()
if result is not None:
    print(f"The value at the given index is: {result}")