import sys

def main():
    if len(sys.argv) < 2:
        print("Please provide an index and at least one argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The first argument must be an integer representing the index.")
        return
    
    if index <= 0 or index >= len(sys.argv):
        print(f"Index {index} is out of range. Please provide a valid index.")
        return
    
    print(sys.argv[index])

if __name__ == "__main__":
    main()