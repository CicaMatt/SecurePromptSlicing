def get_value_from_array(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    raise IndexError("Index out of range")

def main():
    id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # Example array
    size = len(id_sequence)
    
    try:
        index = int(input("Enter an integer: "))
        result = get_value_from_array(id_sequence, size, index)
        print(result)
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()