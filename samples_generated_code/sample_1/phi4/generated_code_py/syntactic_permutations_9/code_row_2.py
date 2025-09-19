import sys

def main():
    if len(sys.argv) < 2:
        print("Please provide an index.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The provided index must be an integer.")
        return
    
    if len(sys.argv) <= index + 1:
        print(f"No argument found at position {index}.")
    else:
        print(sys.argv[index + 1])

if __name__ == "__main__":
    main()