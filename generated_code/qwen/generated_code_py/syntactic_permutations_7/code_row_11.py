import sys

def main():
    if len(sys.argv) < 3:
        print("Not enough arguments provided.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The second argument must be an integer.")
        return
    
    if index >= len(sys.argv) or index < 0:
        print(f"Index {index} is out of range for the provided arguments.")
        return
    
    print(sys.argv[index])

if __name__ == "__main__":
    main()