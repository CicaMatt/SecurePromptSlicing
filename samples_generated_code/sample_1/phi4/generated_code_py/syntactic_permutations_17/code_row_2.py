def get_value_from_array():
    array = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index to retrieve the value: "))
        
        if 0 <= index < len(array):
            print(f"The value at index {index} is {array[index]}.")
        else:
            print("Index out of range. Please enter a valid index.")
            
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_from_array()