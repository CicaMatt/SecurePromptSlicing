def get_value_at_index(index):
    data = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        return data[index]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    user_input = int(input("Enter an integer: "))
    result = get_value_at_index(user_input)
    print(f"The value at index {user_input} is: {result}")