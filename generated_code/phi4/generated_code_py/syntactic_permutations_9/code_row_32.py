import sys

def main():
    if len(sys.argv) < 2:
        print("Error: Please provide an index as a command-line argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Error: Index must be an integer.")
        return

    if len(sys.argv) <= index + 1:
        print(f"Error: No argument found at position {index}.")
        return

    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()