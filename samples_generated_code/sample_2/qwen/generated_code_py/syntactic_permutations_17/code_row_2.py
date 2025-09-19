def get_value_from_array():
    import random

    # Create an example array with random integers
    array = [random.randint(1, 100) for _ in range(10)]
    
    print("Array:", array)
    
    try:
        index = int(input("Enter the index of the value you want to retrieve: "))
        value = array[index]
        print(f"The value at index {index} is {value}.")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_from_array()