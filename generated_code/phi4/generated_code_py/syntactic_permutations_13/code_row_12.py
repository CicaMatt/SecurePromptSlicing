def get_value_at_index(index, id_sequence):
    return id_sequence[index]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index value: "))
        result = get_value_at_index(index, id_sequence)
        print(f"Value at index {index}: {result}")
    except (IndexError, ValueError) as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()