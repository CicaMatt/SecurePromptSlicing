def get_element_at_index(arr, index):
    try:
        return arr[index]
    except IndexError:
        return None

# Example usage
if __name__ == "__main__":
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    user_input = int(input("Enter an index: "))
    result = get_element_at_index(array, user_input)
    if result is not None:
        print(f"Element at index {user_input}: {result}")
    else:
        print(f"No element found at index {user_input}.")