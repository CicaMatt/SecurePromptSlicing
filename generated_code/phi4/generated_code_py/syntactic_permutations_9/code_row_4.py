import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: ./argv_index <index>")
        return
    
    try:
        index = int(sys.argv[1])
        if index < 0 or index >= len(sys.argv) - 1:
            print(f"Error: Index out of range. Valid indices are from 0 to {len(sys.argv) - 2}.")
            return
        print(sys.argv[index + 1])
    except ValueError:
        print("Error: The first argument must be an integer.")

if __name__ == "__main__":
    main()