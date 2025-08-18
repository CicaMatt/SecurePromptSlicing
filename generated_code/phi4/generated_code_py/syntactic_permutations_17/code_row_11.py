def get_element_from_array():
    import sys

    # Example array
    arr = [10, 20, 30, 40, 50, 60]

    try:
        index = int(input("Enter an index: "))
        
        if index < 0 or index >= len(arr):
            print(f"Index {index} is out of bounds.")
        else:
            print(f"The element at index {index} is: {arr[index]}")
    
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    get_element_from_array()