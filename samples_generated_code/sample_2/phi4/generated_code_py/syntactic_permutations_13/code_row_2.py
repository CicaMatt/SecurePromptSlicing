def get_value_at_index(index):
    id_sequence = [101, 202, 303, 404, 505]
    return id_sequence[index]

def main():
    index = int(input("Enter an index value: "))
    result = get_value_at_index(index)
    print(f"Value at index {index}: {result}")

if __name__ == "__main__":
    main()