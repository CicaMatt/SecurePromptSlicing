def get_value_at_index():
    id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    
    index = int(input("Enter an index value: "))
    
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError("Index out of range")

# Example usage
if __name__ == "__main__":
    result = get_value_at_index()
    print(result)