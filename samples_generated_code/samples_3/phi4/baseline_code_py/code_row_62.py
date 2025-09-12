def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError("Index out of range")

def main():
    try:
        index = int(input("Enter an index value: "))
        result = get_value_at_index(index)
        print(f"The value at index {index} is {result}.")
    except ValueError:
        print("Please enter a valid integer.")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()