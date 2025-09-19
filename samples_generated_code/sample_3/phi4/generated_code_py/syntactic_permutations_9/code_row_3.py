import sys

def main():
    if len(sys.argv) < 3:
        print("Error: No index provided or insufficient arguments.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Error: The index must be an integer.")
        return
    
    if index < 0 or index >= len(sys.argv) - 1:
        print(f"Error: Index {index} is out of range for the provided arguments.")
        return

    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()