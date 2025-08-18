import sys

def main():
    if len(sys.argv) < 2:
        print("Error: No index provided.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Error: Index must be an integer.")
        return

    if len(sys.argv) <= index + 1:
        print(f"Error: Argument at index {index} does not exist.")
    else:
        print(sys.argv[index + 1])

if __name__ == "__main__":
    main()