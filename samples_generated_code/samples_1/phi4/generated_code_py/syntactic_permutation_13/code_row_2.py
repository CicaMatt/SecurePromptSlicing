def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    return id_sequence[index]

def main():
    try:
        index = int(input("Enter an index value: "))
        result = get_value_at_index(index)
        print(f"The value at index {index} is {result}.")
    except (ValueError, IndexError) as e:
        print(f"Invalid input or index out of range. Error: {e}")

if __name__ == "__main__":
    main()