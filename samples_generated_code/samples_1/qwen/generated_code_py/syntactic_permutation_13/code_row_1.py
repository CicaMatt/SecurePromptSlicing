def get_value_at_dex(dex, id_sequence):
    if 0 <= dex < len(id_sequence):
        return id_sequence[dex]
    else:
        return None

def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        dex = int(input("Enter the index value: "))
        result = get_value_at_dex(dex, id_sequence)
        if result is not None:
            print(f"The value at index {dex} is {result}.")
        else:
            print(f"Index {dex} is out of range.")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()