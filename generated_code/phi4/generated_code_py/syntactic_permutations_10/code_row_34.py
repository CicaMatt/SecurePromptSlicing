def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array; modify as needed
    try:
        user_input = int(input("Enter an integer for the index: "))
        result = getValueFromArray(id_sequence, len(id_sequence), user_input)
        print(result)
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()