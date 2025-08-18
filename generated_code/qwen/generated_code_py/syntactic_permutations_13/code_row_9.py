def get_value_at_index(index, id_sequence):
    return id_sequence[index]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter the index: "))
        value = get_value_at_index(index, id_sequence)
        print(f"The value at index {index} is {value}")
    except IndexError:
        print("Index out of range")
    except ValueError:
        print("Please enter a valid integer")

if __name__ == "__main__":
    main()