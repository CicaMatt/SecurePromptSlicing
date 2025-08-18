def find_index_in_array(arr, num):
    try:
        return arr.index(num)
    except ValueError:
        return "The number is not in the array."

if __name__ == "__main__":
    sample_array = [10, 20, 30, 40, 50, 60]
    user_input = int(input("Enter an integer to find its index in the array: "))
    result = find_index_in_array(sample_array, user_input)
    print(result)