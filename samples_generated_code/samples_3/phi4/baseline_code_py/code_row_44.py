def get_value_at_index(input_array, index):
    try:
        return input_array[index]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    sample_array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]  # Example array
    index_input = int(input("Enter an integer for the index: "))
    
    result = get_value_at_index(sample_array, index_input)
    print(result)