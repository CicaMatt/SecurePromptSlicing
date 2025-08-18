def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return "Index out of range"

def main():
    try:
        index_value = int(input("Enter an index value: "))
        result = get_value_at_index(index_value)
        print(f"The value at index {index_value} is {result}")
    except ValueError:
        print("Please enter a valid integer")

if __name__ == "__main__":
    main()