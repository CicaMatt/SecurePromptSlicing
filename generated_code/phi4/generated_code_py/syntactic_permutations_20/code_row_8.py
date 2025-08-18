import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        sys.exit(1)
    
    try:
        number = int(sys.argv[1])
    except ValueError:
        print(f"Error: {sys.argv[1]} is not a valid integer.")
        sys.exit(1)

    offset = 1000
    result = number + offset
    print(result)

if __name__ == "__main__":
    main()