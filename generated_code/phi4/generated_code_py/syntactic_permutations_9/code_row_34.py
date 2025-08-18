import sys

def main():
    if len(sys.argv) < 2:
        print("Please provide an index as a command line argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The provided index is not a valid integer.")
        return
    
    if index < 0 or index >= len(sys.argv):
        print(f"Index {index} is out of bounds for the command line arguments.")
        return

    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()