def get_id_at_index(index, id_sequence):
    return id_sequence[index]

def main():
    id_sequence = [101, 203, 305, 407, 509]
    try:
        index = int(input("Enter an index value: "))
        result = get_id_at_index(index, id_sequence)
        print(f"The ID at index {index} is {result}.")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    main()