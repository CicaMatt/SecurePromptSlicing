def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50, 60, 70]
    try:
        return id_sequence[index]
    except IndexError:
        return "Index out of range"

def main():
    index = int(input("Enter the index to retrieve value from id_sequence: "))
    result = get_value_at_index(index)
    print(f"Value at index {index}: {result}")

if __name__ == "__main__":
    main()