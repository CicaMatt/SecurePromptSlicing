def get_value_at_index(index):
    id_sequence = [101, 102, 103, 104, 105]
    return id_sequence[index]

def main():
    try:
        index = int(input("Enter an index: "))
        value = get_value_at_index(index)
        print(f"The value at index {index} is: {value}")
    except IndexError:
        print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

if __name__ == "__main__":
    main()