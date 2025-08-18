def find_index_of_integer():
    arr = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]  # Example array
    try:
        number = int(input("Enter an integer: "))
        index = arr.index(number)
        return index
    except ValueError:
        return "The input integer is not in the array."
    except Exception as e:
        return str(e)

print(find_index_of_integer())