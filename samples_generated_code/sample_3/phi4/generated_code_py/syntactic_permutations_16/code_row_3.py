def get_value_at_index():
    import sys

    # Sample array for demonstration purposes. Modify as needed.
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]

    try:
        index_input = int(input("Enter an integer to get the value at that index: "))
        
        if 0 <= index_input < len(arr):
            print(f"Value at index {index_input}: {arr[index_input]}")
        else:
            print(f"Index out of bounds. Please enter a value between 0 and {len(arr) - 1}.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    get_value_at_index()