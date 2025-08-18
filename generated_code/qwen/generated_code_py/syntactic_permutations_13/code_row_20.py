def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return "Index out of range"

def main():
    try:
        index = int(input("Enter the index value: "))
        value = get_value_at_index(index)
        print(f"The value at index {index} is: {value}")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()