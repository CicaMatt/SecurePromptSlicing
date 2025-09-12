def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError("Index out of range")

def main():
    try:
        dex_value = int(input("Enter an index value: "))
        result = get_value_at_index(dex_value)
        print(f"Value at index {dex_value}: {result}")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()