def get_value_at_index():
    id_sequence = [101, 102, 103, 104, 105]
    
    try:
        index_value = int(input("Enter an index value: "))
        return id_sequence[index_value]
    except (ValueError, IndexError):
        return "Invalid index or input."

# Example of using the function
if __name__ == "__main__":
    result = get_value_at_index()
    print(result)