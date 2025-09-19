import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: ./argv_index <index>")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Index must be an integer.")
        return
    
    if index < 0 or index >= len(sys.argv):
        print(f"Argument at index {index} does not exist. Provide an index between 0 and {len(sys.argv) - 1}.")
    else:
        print(sys.argv[index])

if __name__ == "__main__":
    main()