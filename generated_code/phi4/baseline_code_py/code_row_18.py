def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        idx = int(input("Enter an integer index: "))
        return arr[idx]
    except (ValueError, IndexError) as e:
        print(f"Invalid input or index out of range: {e}")

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(result)