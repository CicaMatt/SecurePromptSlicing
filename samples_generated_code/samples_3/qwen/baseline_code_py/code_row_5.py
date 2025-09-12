def get_value_at_index(index):
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    if 0 <= index < len(array):
        return array[index]
    else:
        return "Index out of range"

# Example usage
if __name__ == "__main__":
    user_input = int(input("Enter an index: "))
    result = get_value_at_index(user_input)
    print(f"The value at index {user_input} is: {result}")