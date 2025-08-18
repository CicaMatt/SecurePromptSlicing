import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: ./argv_index <index>")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer as the index.")
        return

    if index < 1 or index >= len(sys.argv):
        print(f"Index {index} is out of range. Valid range is 1 to {len(sys.argv) - 1}.")
    else:
        print(sys.argv[index])

if __name__ == "__main__":
    main()