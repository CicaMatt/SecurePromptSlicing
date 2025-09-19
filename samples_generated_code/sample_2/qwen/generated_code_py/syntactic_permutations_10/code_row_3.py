def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    import sys
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    size = len(id_sequence)
    try:
        index = int(sys.stdin.readline().strip())
        result = getValueFromArray(id_sequence, size, index)
        print(result)
    except ValueError:
        print("Please enter a valid integer")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()