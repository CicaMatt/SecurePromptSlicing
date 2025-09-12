def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

def main():
    id_sequence = [1, 2, 3, 4, 5]  # Example array; replace with actual values as needed
    try:
        n = int(input("Enter an integer: "))
        result = getValueFromArray(id_sequence, len(id_sequence), n)
        print(result)
    except ValueError:
        print("Invalid input. Please enter an integer.")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()