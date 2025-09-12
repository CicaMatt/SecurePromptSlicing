def get_value_at_index(array, index):
    try:
        return array[index]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    # Example array
    example_array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]

    # Taking integer input from the user
    index_input = int(input("Enter an integer for the index: "))

    # Getting value at the specified index
    result = get_value_at_index(example_array, index_input)

    # Printing the result
    print(f"The value at index {index_input} is: {result}")