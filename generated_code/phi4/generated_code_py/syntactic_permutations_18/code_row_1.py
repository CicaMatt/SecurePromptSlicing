def get_value_at_index(array, index):
    try:
        return array[index]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    my_array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]  # Example array
    index = int(input("Enter the index: "))
    result = get_value_at_index(my_array, index)
    print(f"The value at index {index} is: {result}")