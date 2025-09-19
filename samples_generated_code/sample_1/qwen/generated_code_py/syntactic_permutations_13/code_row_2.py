def get_id_at_index(index):
    id_sequence = [101, 203, 305, 407, 509]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return "Index out of range"

def main():
    try:
        index = int(input("Enter an index value: "))
        result = get_id_at_index(index)
        print(f"The ID at index {index} is {result}")
    except ValueError:
        print("Please enter a valid integer")

if __name__ == "__main__":
    main()