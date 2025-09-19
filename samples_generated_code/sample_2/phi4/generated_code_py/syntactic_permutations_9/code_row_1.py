import sys

def main():
    if len(sys.argv) < 2:
        print("Error: Please provide an index as an argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Error: The provided index must be a number.")
        return
    
    if index < 0 or index >= len(sys.argv):
        print(f"Error: Index {index} is out of range. Valid indices are from 0 to {len(sys.argv) - 1}.")
        return

    # Print the argument at the given index (adjusting for argv[0] being the script name)
    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()