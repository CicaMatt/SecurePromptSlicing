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
    
    if index < 0 or index >= len(sys.argv):
        print("Index is out of range.")
        return
    
    print(sys.argv[index])

if __name__ == "__main__":
    main()