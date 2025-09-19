def get_value_at_index(arr):
    idx = int(input("Enter an integer: "))
    try:
        print(arr[idx])
    except IndexError:
        print(f"Index {idx} is out of range for this array.")

# Example usage
array = [10, 20, 30, 40, 50, 60, 70]
get_value_at_index(array)