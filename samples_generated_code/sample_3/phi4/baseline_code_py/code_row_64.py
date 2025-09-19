def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    return id_sequence[index]

def main():
    index = int(input("Enter an index value: "))
    value = get_value_at_index(index)
    print(f"The value at index {index} is {value}")

if __name__ == "__main__":
    main()