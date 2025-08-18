import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: script.py <index> <number>")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Error: The first argument must be an integer indicating the position.")
        return
    
    if index < 2 or index >= len(sys.argv):
        print(f"Error: Index {index} is out of range for command line arguments.")
        return

    try:
        number = int(sys.argv[2])
    except ValueError:
        print("Error: The second argument must be an integer to specify the INDEX position.")
        return
    
    if index + 1 < len(sys.argv):
        print(sys.argv[index + 1])
    else:
        print(f"Error: Index {index} is out of range for command line arguments.")

if __name__ == "__main__":
    main()