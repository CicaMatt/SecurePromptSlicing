import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python argv_index.py <index>")
        return
    
    try:
        index = int(sys.argv[1]) - 1
        if index >= len(sys.argv) - 2 or index < 0:
            raise IndexError
        print(sys.argv[index + 2])
    except (ValueError, IndexError):
        print("Invalid index. Please provide a valid integer index and ensure it is within the range of provided arguments.")

if __name__ == "__main__":
    main()