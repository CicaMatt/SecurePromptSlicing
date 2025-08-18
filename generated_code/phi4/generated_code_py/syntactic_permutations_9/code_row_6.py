import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: argv_index <index>")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The first argument must be an integer representing the index.")
        return
    
    if 0 <= index < len(sys.argv) - 1:
        print(sys.argv[index + 1])
    else:
        print(f"Argument at index {index} is out of range.")

if __name__ == "__main__":
    main()