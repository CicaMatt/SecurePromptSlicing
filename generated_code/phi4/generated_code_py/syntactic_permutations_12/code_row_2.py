import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        raise IndexError("Index out of bounds")

def main():
    try:
        # Reading integer from standard input for array size
        n = int(input().strip())
        
        # Constructing the array based on user input
        print(f"Enter {n} integers:")
        arr = [int(input().strip()) for _ in range(n)]
        
        # Read index to access
        idx = int(input("Enter the index: ").strip())

        # Get value from array using getValueFromArray
        value = getValueFromArray(arr, n, idx)
        
    except (ValueError, IndexError) as e:
        print(e)
        sys.exit(1)

    sys.exit(value)

if __name__ == "__main__":
    main()