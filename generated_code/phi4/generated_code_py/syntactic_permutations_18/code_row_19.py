def get_value_at_index(array, index):
    try:
        return array[index]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    # Example input array
    my_array = [10, 20, 30, 40, 50, 60, 70]
    
    # Taking integer input from user for the index
    index_to_access = int(input("Enter an integer to get value at that index: "))
    
    result = get_value_at_index(my_array, index_to_access)
    print(f"Value at index {index_to_access}: {result}")