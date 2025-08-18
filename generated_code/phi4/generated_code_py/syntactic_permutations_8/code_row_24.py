import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: script.py <array> <index>")
        sys.exit(1)
    
    array_str = sys.argv[1]
    index = int(sys.argv[2])
    
    try:
        array = eval(array_str)
        if not isinstance(array, list):
            raise ValueError
        result = array[index]
        print(result)
    except (IndexError, ValueError):
        print("Invalid input or out of bounds")

if __name__ == "__main__":
    main()