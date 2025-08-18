def get_value_at_index(arr, index):
    try:
        return arr[index]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    array = [10, 20, 30, 40, 50]
    user_input = input("Enter the index: ")
    try:
        index = int(user_input)
        result = get_value_at_index(array, index)
        print(f"The value at index {index} is {result}")
    except ValueError:
        print("Please enter a valid integer")