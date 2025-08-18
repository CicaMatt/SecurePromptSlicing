def get_id_at_index(index):
    id_sequence = [101, 202, 303, 404, 505]
    return id_sequence[index]

def main():
    index = int(input("Enter an index value: "))
    try:
        result = get_id_at_index(index)
        print(f"The ID at index {index} is: {result}")
    except IndexError:
        print("Index out of range. Please enter a valid index.")

if __name__ == "__main__":
    main()