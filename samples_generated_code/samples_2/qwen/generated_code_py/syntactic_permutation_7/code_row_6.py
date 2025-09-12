import sys

def main():
    if len(sys.argv) < 2:
        print("Not enough arguments provided.")
        return
    
    try:
        index = int(sys.argv[1])
        if index >= len(sys.argv):
            print(f"Index {index} is out of range for command line arguments.")
        else:
            print(sys.argv[index])
    except ValueError:
        print("The second argument must be an integer.")

if __name__ == "__main__":
    main()