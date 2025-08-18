import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: argv_index <index>")
        return
    
    try:
        index = int(sys.argv[1])
        if index >= 0 and index < len(sys.argv):
            print(sys.argv[index + 1])
        else:
            print(f"Index {index} is out of range.")
    except ValueError:
        print("Please provide a valid integer as the index.")

if __name__ == "__main__":
    main()