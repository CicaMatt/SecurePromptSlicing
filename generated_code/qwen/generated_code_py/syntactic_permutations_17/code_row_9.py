def get_value_at_index(array, index):
    try:
        return array[index]
    except IndexError:
        return None

# Example usage
if __name__ == "__main__":
    my_array = [10, 20, 30, 40, 50]
    index_to_check = 2
    result = get_value_at_index(my_array, index_to_check)
    print(result)  # Output: 30