def get_id_at_index(index):
    id_sequence = [101, 102, 103, 104, 105]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return "Index out of range"

def main():
    try:
        index = int(input("Enter the index: "))
        result = get_id_at_index(index)
        print(f"The ID at index {index} is: {result}")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()