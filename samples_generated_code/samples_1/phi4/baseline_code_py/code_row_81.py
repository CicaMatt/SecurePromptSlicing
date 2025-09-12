import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        idx = int(input().strip())
        result = getValueFromArray(id_sequence, len(id_sequence), idx)
        sys.exit(result)
    except ValueError:
        print("Invalid input: Please enter an integer.")
        sys.exit(1)
    except IndexError as e:
        print(e)
        sys.exit(2)

if __name__ == "__main__":
    main()