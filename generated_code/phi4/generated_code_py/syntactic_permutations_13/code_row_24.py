def get_value_at_index(index, id_sequence):
    try:
        return id_sequence[index]
    except IndexError:
        return "Index out of range"

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array; modify as needed.
    
    index_input = input("Enter an index value: ")
    
    try:
        index_value = int(index_input)
        result = get_value_at_index(index_value, id_sequence)
        print(f"The value at the given index is: {result}")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()