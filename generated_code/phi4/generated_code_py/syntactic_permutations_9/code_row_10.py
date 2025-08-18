import sys

def main():
    if len(sys.argv) < 2:
        print("Error: Please provide an index.")
        return
    
    try:
        index = int(sys.argv[1])
        if index < 1 or index >= len(sys.argv):
            raise IndexError
        
        print(sys.argv[index])
    
    except ValueError:
        print("Error: The provided index is not a valid integer.")
    except IndexError:
        print(f"Error: Index {index} is out of range for the given arguments.")

if __name__ == "__main__":
    main()