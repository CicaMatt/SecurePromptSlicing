def get_value_at_index():
    import sys

    id_sequence = [10, 20, 30, 40, 50]  # Example array; replace with actual data if needed.

    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (ValueError, IndexError):
        print("Invalid input or out of range. Please enter a valid integer within the array's bounds.")
        sys.exit(1)

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"Value at entered index: {result}")