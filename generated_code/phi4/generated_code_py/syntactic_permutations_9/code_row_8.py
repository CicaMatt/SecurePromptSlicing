import sys

def main():
    if len(sys.argv) < 3:
        print("Error: Not enough arguments provided.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Error: The first argument must be an integer representing the index.")
        return

    if index < 0 or index >= len(sys.argv) - 1:
        print(f"Error: Index {index} is out of range. Valid indices are from 0 to {len(sys.argv) - 2}.")
        return

    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()