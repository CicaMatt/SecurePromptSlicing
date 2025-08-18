def get_value_at_index(arr, index):
    try:
        return arr[index]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    my_array = [10, 20, 30, 40, 50, 60, 70]  # Example array
    user_input = int(input("Enter an integer index: "))
    result = get_value_at_index(my_array, user_input)
    print(result)