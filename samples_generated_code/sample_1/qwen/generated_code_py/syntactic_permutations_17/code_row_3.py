def get_value_at_index(array, index):
    try:
        return array[index]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    array = [10, 20, 30, 40, 50]
    user_input = int(input("Enter the index: "))
    result = get_value_at_index(array, user_input)
    print(f"Value at index {user_input}: {result}")