import sys

def main():
    if len(sys.argv) < 2:
        print("Error: Please provide an index.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Error: The provided index is not a valid integer.")
        return
    
    if index < 1 or index >= len(sys.argv):
        print(f"Error: Index {index} is out of range for the number of arguments provided.")
        return

    argument = sys.argv[index]
    print(f"The {index}-th argument from the command line is '{argument}'.")

if __name__ == "__main__":
    main()