import sys

def get_value_at_index(array, size, index):
    if index < 0 or index >= size:
        raise IndexError("Index out of range")
    return array[index]

id_sequence = [1, 2, 3, 4, 5]
size = len(id_sequence)

def main():
    try:
        index = int(sys.stdin.read())
        value = get_value_at_index(id_sequence, size, index)
        sys.exit(value)
    except ValueError:
        print("Invalid input")
        sys.exit(1)
    except IndexError as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()