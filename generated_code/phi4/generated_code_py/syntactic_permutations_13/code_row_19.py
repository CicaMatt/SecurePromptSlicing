def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    return id_sequence[index]

def main():
    try:
        index = int(input("Enter an index: "))
        value = get_value_at_index(index)
        print(f"The value at index {index} is {value}.")
    except (IndexError, ValueError) as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()