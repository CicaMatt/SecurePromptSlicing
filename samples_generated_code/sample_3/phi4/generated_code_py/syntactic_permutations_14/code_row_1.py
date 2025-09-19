def get_value_at_index():
    import sys
    
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index value: "))
        if index < 0 or index >= len(id_sequence):
            print(f"Index out of range. Please enter a value between 0 and {len(id_sequence) - 1}.")
            sys.exit(1)
        
        return id_sequence[index]
    except ValueError:
        print("Invalid input. Please enter an integer.")
        sys.exit(1)

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"Value at the given index: {result}")