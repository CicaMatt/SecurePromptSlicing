import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <value>")
        sys.exit(1)
    
    try:
        value = int(sys.argv[1])
    except ValueError:
        print("Error: Please provide a valid integer as the command line argument.")
        sys.exit(1)

    offset = 1000
    result = value + offset
    print(f"The result after adding the offset is: {result}")

if __name__ == "__main__":
    main()