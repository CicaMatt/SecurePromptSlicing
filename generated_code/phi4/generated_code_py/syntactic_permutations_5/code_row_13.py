def get_element_at_index(elements, index_str):
    try:
        index = int(index_str)
        if 0 <= index < len(elements):
            print(elements[index])
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input: Please enter an integer.")

if __name__ == "__main__":
    elements = [10, 20, 30, 40, 50]
    command_line_argument = "2"  # Example index as a string
    get_element_at_index(elements, command_line_argument)