import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: argv_index <index>")
        return
    
    try:
        index = int(sys.argv[1])
        if index >= 0 and index < len(sys.argv) - 1:
            print(sys.argv[index + 1])
        else:
            print(f"Index {index} is out of range for the provided arguments.")
    except ValueError:
        print("Please provide a valid integer as an index.")

if __name__ == "__main__":
    main()