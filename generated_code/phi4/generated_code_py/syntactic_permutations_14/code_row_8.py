def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]  # Example sequence; replace with desired values
    try:
        index = int(input("Enter an index: "))
        return id_sequence[index]
    except (IndexError, ValueError):
        return "Invalid index. Please enter a valid integer within the range of the array."

# Example usage
if __name__ == "__main__":
    result = get_value_at_index()
    print(result)