def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    return id_sequence[index]

def main():
    try:
        index = int(input("Enter an index value: "))
        result = get_value_at_index(index)
        print(f"The value at index {index} is: {result}")
    except (IndexError, ValueError):
        print("Invalid index. Please enter a valid integer within the range of the array.")

if __name__ == "__main__":
    main()