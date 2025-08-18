def get_value_at_index():
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        index = int(input("Enter an integer index: "))
        return array[index]
    except (ValueError, IndexError) as e:
        print(f"Error: {e}")
        return None

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"The value at the given index is: {result}")