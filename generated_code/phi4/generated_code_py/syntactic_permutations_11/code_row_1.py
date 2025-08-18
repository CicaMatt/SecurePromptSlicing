def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        raise IndexError("Index out of bounds")

def main():
    import sys
    input = sys.stdin.read
    id_sequence = [1, 2, 3, 4, 5]  # Example array; replace as needed.
    try:
        n = int(input().strip())
        result = getValueFromArray(id_sequence, len(id_sequence), n)
        print(result)
    except Exception as e:
        sys.exit(str(e))

if __name__ == "__main__":
    main()