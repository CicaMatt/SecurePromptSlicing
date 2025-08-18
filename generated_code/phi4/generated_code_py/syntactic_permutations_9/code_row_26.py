import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python argv_index.py [index]")
        return

    try:
        index = int(sys.argv[1])
        if index >= len(sys.argv) - 1 or index < 0:
            print(f"Index {index} is out of range.")
            return
        print(sys.argv[index + 1])
    except ValueError:
        print("Please provide a valid integer as the first argument for the index.")

if __name__ == "__main__":
    main()