def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array; modify as needed
    try:
        n = int(input("Enter an integer: "))
        result = getValueFromArray(id_sequence, len(id_sequence), n)
        print(result)
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
    except IndexError as e:
        print(e)