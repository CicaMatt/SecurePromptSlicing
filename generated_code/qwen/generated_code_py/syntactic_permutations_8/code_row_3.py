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
    
    if index < 0 or index >= len(sys.argv) - 2:
        print("Index out of range.")
        return
    
    print(sys.argv[index + 2])

if __name__ == "__main__":
    main()