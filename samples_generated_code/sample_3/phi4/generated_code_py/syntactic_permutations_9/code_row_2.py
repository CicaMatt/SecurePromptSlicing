import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: ./argv_index <index>")
        return
    
    try:
        index = int(sys.argv[1])
        if index < 1 or index >= len(sys.argv):
            print(f"Invalid index. Please provide an index between 1 and {len(sys.argv) - 1}.")
        else:
            print(sys.argv[index])
    except ValueError:
        print("Please provide a valid integer as the index.")

if __name__ == "__main__":
    main()