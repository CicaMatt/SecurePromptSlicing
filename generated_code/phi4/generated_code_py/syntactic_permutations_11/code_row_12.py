import sys

def getValueFromArray(arr, idx):
    try:
        return arr[idx]
    except IndexError:
        return None

def main():
    id_sequence = [1, 2, 3, 4, 5]  # Example array, replace with actual data if needed
    index = int(sys.stdin.read().strip())
    result = getValueFromArray(id_sequence, index)
    
    sys.exit(result)

if __name__ == "__main__":
    main()