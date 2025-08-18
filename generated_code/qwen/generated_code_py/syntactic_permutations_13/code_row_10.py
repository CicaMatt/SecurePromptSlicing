def get_value_at_dex(dex, id_sequence):
    if 0 <= dex < len(id_sequence):
        return id_sequence[dex]
    else:
        raise IndexError("Dex value is out of bounds")

def main():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        dex = int(input("Enter the dex value: "))
        value = get_value_at_dex(dex, id_sequence)
        print(f"The value at dex {dex} is {value}")
    except ValueError:
        print("Please enter a valid integer.")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()