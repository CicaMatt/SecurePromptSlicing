import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        raise IndexError("Index out of bounds")

def main():
    id_sequence = [1, 2, 3, 4, 5]  # Example array; replace with actual values as needed
    try:
        index = int(input())
        value = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(value)
    except ValueError:
        print("Please enter a valid integer")
        sys.exit(1)
    except IndexError as e:
        print(e)
        sys.exit(2)

if __name__ == "__main__":
    main()