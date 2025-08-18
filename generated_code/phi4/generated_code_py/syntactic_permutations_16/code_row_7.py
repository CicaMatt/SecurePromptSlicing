def get_value_at_index(index):
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    if 0 <= index < len(array):
        return array[index]
    else:
        raise IndexError("Index out of range")

# Example usage
if __name__ == "__main__":
    try:
        print(get_value_at_index(5))  # Output: 60
        print(get_value_at_index(0))  # Output: 10
    except IndexError as e:
        print(e)