def get_value_at_dex(dex, id_sequence):
    return id_sequence[dex]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        dex = int(input("Enter the index value: "))
        value = get_value_at_dex(dex, id_sequence)
        print(f"The value at index {dex} is {value}.")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    main()