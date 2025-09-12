import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: ./argv_index index")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Index must be an integer.")
        return
    
    if index < 0 or index >= len(sys.argv):
        print(f"Index {index} out of range. Valid indices are from 0 to {len(sys.argv) - 1}.")
        return

    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()