import sys

def main():
    try:
        index = int(sys.argv[1])
        if index < 1 or index >= len(sys.argv):
            raise IndexError("Index out of range")
        print(sys.argv[index + 1])
    except (IndexError, ValueError) as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()