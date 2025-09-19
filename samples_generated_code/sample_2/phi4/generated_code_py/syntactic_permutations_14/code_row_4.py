def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (ValueError, IndexError):
        print("Invalid index. Please enter a valid integer within the range of the list.")
        return None

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"Value at entered index: {result}")