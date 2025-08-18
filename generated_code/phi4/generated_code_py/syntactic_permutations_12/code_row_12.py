import sys

def getValueFromArray(arr, idx):
    try:
        return arr[idx]
    except IndexError:
        return None

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> [array elements separated by spaces]")
        sys.exit(1)

    index = int(sys.argv[1])
    array = list(map(int, sys.argv[2:]))

    value = getValueFromArray(array, index)
    
    if value is not None:
        sys.exit(value)
    else:
        sys.exit(-1)  # or another code indicating an error

if __name__ == "__main__":
    main()