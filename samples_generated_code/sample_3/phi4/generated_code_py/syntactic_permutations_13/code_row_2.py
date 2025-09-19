def get_id_at_index(index):
    id_sequence = [101, 202, 303, 404, 505]
    return id_sequence[index]

def main():
    try:
        index = int(input("Enter an index value: "))
        result = get_id_at_index(index)
        print(f"Value at index {index}: {result}")
    except IndexError:
        print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

if __name__ == "__main__":
    main()