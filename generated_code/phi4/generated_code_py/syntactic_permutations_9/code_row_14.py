import sys

def main():
    if len(sys.argv) < 2:
        print("Error: Please provide an index.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Error: The provided index must be an integer.")
        return
    
    if index <= 0 or index >= len(sys.argv):
        print(f"Error: Index {index} is out of range. Must be between 1 and {len(sys.argv) - 1}.")
        return

    print(sys.argv[index])

if __name__ == "__main__":
    main()