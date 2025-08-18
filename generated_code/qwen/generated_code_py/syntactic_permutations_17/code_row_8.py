def get_value_at_index():
    try:
        input_array = list(map(int, input("Enter the elements of the array separated by spaces: ").split()))
        index = int(input("Enter the index to retrieve the value from: "))
        print(f"The value at index {index} is {input_array[index]}")
    except IndexError:
        print("Index out of range.")
    except ValueError:
        print("Please enter valid integers for both the array elements and the index.")

get_value_at_index()