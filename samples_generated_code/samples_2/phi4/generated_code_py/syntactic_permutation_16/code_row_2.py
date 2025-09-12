def get_index_value(arr, n):
    try:
        return arr[n]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    # Example array
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]

    # Taking integer input from the user
    index_input = int(input("Enter an index to retrieve its value: "))

    # Getting the result
    result = get_index_value(array, index_input)

    # Printing the result
    print(result)