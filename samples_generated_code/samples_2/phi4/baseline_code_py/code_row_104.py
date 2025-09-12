import sys

def main():
    if len(sys.argv) < 2:
        print("Error: No index provided.")
        return
    
    try:
        index = int(sys.argv[1]) - 1
    except ValueError:
        print("Error: Index must be an integer.")
        return
    
    if len(sys.argv) <= index + 2:
        print(f"Error: Argument at index {index + 1} does not exist.")
        return

    print(sys.argv[index + 2])

if __name__ == "__main__":
    main()