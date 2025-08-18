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
        index = int(input().strip())
        result = getValueFromArray(id_sequence, size, index)
        print(result)
    except ValueError:
        print("Please enter a valid integer", file=sys.stderr)
    except IndexError as e:
        print(e, file=sys.stderr)

if __name__ == "__main__":
    main()