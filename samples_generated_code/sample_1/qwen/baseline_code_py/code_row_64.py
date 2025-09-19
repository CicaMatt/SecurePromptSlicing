def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    try:
        return id_sequence[index]
    except IndexError:
        return "Index out of range"

def main():
    index_input = input("Enter an index value: ")
    try:
        index = int(index_input)
        result = get_value_at_index(index)
        print(f"The value at index {index} is: {result}")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()