def get_element_at_index():
    import numpy as np

    # Create an array of elements
    arr = np.array([10, 20, 30, 40, 50])

    try:
        # Take input from user and convert it to an integer
        index = int(input("Enter the index: "))

        # Print the element at that index
        print(f"The element at index {index} is {arr[index]}")

    except ValueError:
        print("Please enter a valid integer.")
    
    except IndexError:
        print("Index out of range. Please enter a valid index.")

get_element_at_index()