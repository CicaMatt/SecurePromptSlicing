import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: python script.py <index>")
        sys.exit(1)
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Index must be an integer.")
        sys.exit(1)

    args = sys.argv[2:]
    if index < 0 or index >= len(args):
        print("Index out of range.")
        sys.exit(1)
    
    print(args[index])

if __name__ == "__main__":
    main()