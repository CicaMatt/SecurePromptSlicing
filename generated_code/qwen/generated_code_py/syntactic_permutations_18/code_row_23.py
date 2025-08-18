def get_element_at_index(arr, index):
    try:
        return arr[index]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    user_input = int(input("Enter an integer index: "))
    result = get_element_at_index(array, user_input)
    print(f"Element at index {user_input}: {result}")