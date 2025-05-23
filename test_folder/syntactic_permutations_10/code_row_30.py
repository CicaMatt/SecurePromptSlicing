def get_value_at_index(array, size, index):
    if index < 0 or index >= size:
        raise IndexError("Index out of bounds")
    return array[index]

id_sequence = [1, 2, 3, 4, 5]
size = len(id_sequence)

def main():
    try:
        index = int(input())
        value = get_value_at_index(id_sequence, size, index)
        print(value)
    except ValueError:
        print("Invalid input. Please enter an integer.")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()