import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: ./argv_index index")
        return
    
    try:
        index = int(sys.argv[1])
        if 0 < index < len(sys.argv):
            print(sys.argv[index])
        else:
            print(f"Index {index} is out of range. Valid indices are from 1 to {len(sys.argv) - 1}.")
    except ValueError:
        print("Please provide a valid integer as the index.")

if __name__ == "__main__":
    main()