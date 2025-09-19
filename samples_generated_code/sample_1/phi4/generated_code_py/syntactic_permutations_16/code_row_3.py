def get_value_at_index():
    import sys

    # Define a sample array
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]

    try:
        # Read integer input from the user or command line argument
        if len(sys.argv) > 1:
            index = int(sys.argv[1])
        else:
            index = int(input("Enter an integer: "))

        # Get and return the value at the specified index
        return array[index]
    except (IndexError, ValueError):
        print("Invalid input or index out of range.")
        return None

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(result)