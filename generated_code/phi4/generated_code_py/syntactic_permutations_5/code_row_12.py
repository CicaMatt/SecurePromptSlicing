import numpy as np

def get_element_at_index_from_string(array_elements, index_as_string):
    # Create an array from input elements
    array = np.array(array_elements)
    
    # Convert string index to integer
    index = int(index_as_string)
    
    # Print the element at that index
    print(array[index])

# Example usage:
array_elements = [10, 20, 30, 40, 50]
index_as_string = '2'
get_element_at_index_from_string(array_elements, index_as_string)