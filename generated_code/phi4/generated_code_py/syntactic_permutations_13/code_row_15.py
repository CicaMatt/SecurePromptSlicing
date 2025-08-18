def get_value_at_index(index):
    values = [10, 20, 30, 40, 50]
    try:
        return values[index]
    except IndexError:
        return "Index out of range."

def main():
    try:
        index = int(input("Enter an index value: "))
        result = get_value_at_index(index)
        print(f"Value at index {index}: {result}")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()