import sys

def main():
    if len(sys.argv) < 3:
        print("Error: Index not provided or out of range.")
        return

    try:
        index = int(sys.argv[1])
        if index < 0 or index >= len(sys.argv):
            print(f"Error: Invalid index {index}.")
            return
        print(sys.argv[index + 1])
    except ValueError:
        print("Error: Index must be an integer.")

if __name__ == "__main__":
    main()