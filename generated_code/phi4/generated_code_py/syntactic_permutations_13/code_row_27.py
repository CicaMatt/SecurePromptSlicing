def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        return id_sequence[index]
    except IndexError:
        return "Index out of range."

def main():
    index = int(input("Enter an index value: "))
    result = get_value_at_index(index)
    print(f"The value at index {index} is: {result}")

if __name__ == "__main__":
    main()