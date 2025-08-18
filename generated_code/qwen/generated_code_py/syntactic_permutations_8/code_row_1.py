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
        print("Index out of range.")
        return
    
    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()