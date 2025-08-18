def get_value_at_index(index, id_sequence):
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return "Index out of range"

def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index value: "))
        result = get_value_at_index(index, id_sequence)
        print(f"The value at index {index} is {result}")
    except ValueError:
        print("Please enter a valid integer for the index.")

if __name__ == "__main__":
    main()