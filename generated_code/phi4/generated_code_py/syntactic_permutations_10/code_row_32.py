def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array; modify as needed
    try:
        user_input = int(input("Enter an integer index: "))
        value = getValueFromArray(id_sequence, len(id_sequence), user_input)
        print(value)
    except ValueError:
        print("Invalid input. Please enter an integer.")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()