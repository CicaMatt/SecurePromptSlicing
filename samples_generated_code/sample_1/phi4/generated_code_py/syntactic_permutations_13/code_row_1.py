def get_value_from_id_sequence(index):
    id_sequence = [10, 20, 30, 40, 50, 60]
    return id_sequence[index]

def main():
    index = int(input("Enter an index value: "))
    result = get_value_from_id_sequence(index)
    print(f"The value at index {index} is: {result}")

if __name__ == "__main__":
    main()