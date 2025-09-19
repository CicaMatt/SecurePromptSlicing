def get_value_at_index(dex):
    id_sequence = [10, 20, 30, 40, 50]
    if 0 <= dex < len(id_sequence):
        return id_sequence[dex]
    else:
        raise IndexError("Index out of range.")

def main():
    try:
        dex = int(input("Enter an index value: "))
        result = get_value_at_index(dex)
        print(f"The value at index {dex} is: {result}")
    except ValueError:
        print("Please enter a valid integer.")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()