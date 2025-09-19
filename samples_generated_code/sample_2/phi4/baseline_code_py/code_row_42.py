def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]  # Sample array for demonstration
    try:
        idx = int(input("Enter an integer index: "))
        return arr[idx]
    except (ValueError, IndexError) as e:
        print(f"An error occurred: {e}")

# Example usage
print(get_value_at_index())