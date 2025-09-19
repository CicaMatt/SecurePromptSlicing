def get_value_from_array():
    numbers = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index to retrieve its corresponding value from the array: "))
        
        if 0 <= index < len(numbers):
            print(f"The value at index {index} is {numbers[index]}.")
        else:
            print("Index out of range. Please enter a valid index.")
    
    except ValueError:
        print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    get_value_from_array()