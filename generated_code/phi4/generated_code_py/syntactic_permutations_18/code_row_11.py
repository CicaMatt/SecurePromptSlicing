def get_value_from_array(index):
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    if 0 <= index < len(array):
        return array[index]
    else:
        return "Index out of range"

# Example usage
if __name__ == "__main__":
    user_input = int(input("Enter an integer for the index: "))
    result = get_value_from_array(user_input)
    print(result)