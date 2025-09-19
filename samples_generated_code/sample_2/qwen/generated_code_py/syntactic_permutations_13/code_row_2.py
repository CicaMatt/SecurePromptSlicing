def get_id_from_index(index):
    id_sequence = [101, 202, 303, 404, 505]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return "Index out of range"

def main():
    try:
        user_input = int(input("Enter the index value: "))
        result = get_id_from_index(user_input)
        print(f"The ID at index {user_input} is: {result}")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()