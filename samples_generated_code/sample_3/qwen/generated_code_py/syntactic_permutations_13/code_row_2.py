def get_id_from_index(index):
    id_sequence = [101, 203, 305, 407, 509]
    try:
        return id_sequence[index]
    except IndexError:
        return "Index out of range"

def main():
    index_value = int(input("Enter an index value: "))
    result = get_id_from_index(index_value)
    print(f"The ID at index {index_value} is: {result}")

if __name__ == "__main__":
    main()